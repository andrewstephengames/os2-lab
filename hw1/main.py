import csv
import random

class Factor:
    def __init__(self, id_, name, status, time):
        self.id = id_
        self.name = name
        self.status = status
        self.time = time

    def show(self):
        print(f"[Factor] {self.name} (Status: {self.status}, Time: {self.time})")

class Person(Factor):
    def __init__(self, id_, name, status, time, habit, location, illnesses):
        super().__init__(id_, name, status, time)
        self.habit = habit
        self.location = location
        self.illnesses = illnesses

    def move(self, new_location):
        self.location = new_location

    def get_in(self): print(f"{self.name} enters the space.")
    def get_out(self): print(f"{self.name} leaves the space.")
    def use(self): print(f"{self.name} is interacting.")

class Environment(Factor):
    def __init__(self, temperature, humidity, illumination, noise_level):
        super().__init__("env01", "Environment", "active", "now")
        self.temperature = temperature
        self.humidity = humidity
        self.illumination = illumination
        self.noise_level = noise_level

    def get_environment_info(self):
        return {
            "Temperature": self.temperature,
            "Humidity": self.humidity,
            "Illumination": self.illumination,
            "Noise level": self.noise_level
        }

class Reasoning:
    def __init__(self, db_connection):
        self.db_connection = db_connection
        self.disease_rules = []

    def get_cases(self):
        with open('diseases.csv', newline='') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                self.disease_rules.append(row)

    def case_matching(self, env_info, person):
        results = {}
        for illness in person.illnesses:
            relevant_rules = [r for r in self.disease_rules if r["Disease"] == illness]
            status = []
            for rule in relevant_rules:
                param = rule["Parameter"]
                value = float(env_info[param])
                if self._match(value, rule["Emergency"]):
                    status.append((param, "Emergency"))
                elif self._match(value, rule["Warning"]):
                    status.append((param, "Warning"))
                elif self._match(value, rule["Normal"]):
                    status.append((param, "Normal"))
                elif self._match(value, rule["BelowNormal"]):
                    status.append((param, "BelowNormal"))
            results[illness] = status
        return results

    def _match(self, value, condition):
        if '-' in condition:
            low, high = map(float, condition.split('-'))
            return low <= value <= high
        elif '>' in condition:
            return value > float(condition.strip('>'))
        elif '<' in condition:
            return value < float(condition.strip('<'))
        return False

    def do_reasoning(self, env_info, person):
        results = self.case_matching(env_info, person)
        print(f"\nReasoning Results for {person.name}")
        for illness, factors in results.items():
            print(f"  ↳ {illness}:")
            for param, status in factors:
                print(f"    * {param}: {status}")

class DBConnection:
    def __init__(self, connection_string):
        self.connection_string = connection_string

    def read(self): pass
    def write(self): pass
    def close(self): pass

if __name__ == "__main__":
    env = Environment(
        temperature=random.uniform(5, 45),
        humidity=random.uniform(10, 100),
        illumination=random.uniform(100, 1200),
        noise_level=random.uniform(20, 100)
    )

    person = Person("p01", "Andrew", "awake", "now", "sedentary", "Living Room", ["Asthma", "Flu", "Hypertension"])

    db = DBConnection("localhost:5432")
    reasoner = Reasoning(db)
    reasoner.get_cases()
    env_info = env.get_environment_info()
    reasoner.do_reasoning(env_info, person)

    print(f"\nHello {person.name}, based on your current environment:")
    for param, value in env_info.items():
        print(f"   {param}: {value:.2f}")

