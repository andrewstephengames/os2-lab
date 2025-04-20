class Factor:
    def __init__(self, ID, name, status, time):
        self.ID = ID
        self.name = name
        self.status = status
        self.time = time

    def show(self):
        return f"{self.name}: {self.status}"


class Person:
    def __init__(self, habit, location):
        self.habit = habit
        self.location = location

    def move(self, new_location):
        self.location = new_location

    def get_in(self):
        return f"{self.__class__.__name__} entered {self.location}"

    def get_out(self):
        return f"{self.__class__.__name__} exited {self.location}"

    def use(self, appliance):
        appliance.set_status('on')


class HomeAppliance:
    def __init__(self, location, effect_level):
        self.location = location
        self.effect_level = effect_level

    def set_status(self, status):
        self.status = status


class Environment:
    def __init__(self, temperature, humidity, illumination, noise_level):
        self.temperature = temperature
        self.humidity = humidity
        self.illumination = illumination
        self.noise_level = noise_level

    def get_environment_info(self):
        return {
            "temperature": self.temperature,
            "humidity": self.humidity,
            "illumination": self.illumination,
            "noise_level": self.noise_level
        }


class Internal(Environment):
    def __init__(self, temperature, humidity, illumination, noise_level, size):
        super().__init__(temperature, humidity, illumination, noise_level)
        self.size = size

    def get_environment_from_appliance_effect(self, appliance_effect):
        self.temperature += appliance_effect
        return self.get_environment_info()


class Weather(Environment):
    def __init__(self, temperature, humidity, illumination, noise_level, level):
        super().__init__(temperature, humidity, illumination, noise_level)
        self.level = level

    def set_effect(self, effect):
        self.level = effect


class DBConnection:
    def __init__(self, connection_string):
        self.connection_string = connection_string

    def read(self):
        return "read"

    def write(self):
        return "write"

    def close(self):
        return "closed"


class Reasoning:
    def __init__(self, db_connection, ref_smart_home):
        self.db_connection = db_connection
        self.ref_smart_home = ref_smart_home

    def get_cases(self):
        return []

    def do_reasoning(self, environment_info):
        return "reasoned"

    def case_matching(self):
        return "matched"

    def get_environment_info(self):
        return self.ref_smart_home.get_environment_info()


class VirtualSpace:
    def __init__(self, size, location, factors):
        self.size = size
        self.location = location
        self.factors = factors

    def show(self):
        return f"{self.size} @ {self.location} with {len(self.factors)} factors"

    def get_event(self):
        return "event"

