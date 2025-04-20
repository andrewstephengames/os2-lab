class DiseaseRule:
    def __init__(self, name, thresholds):
        self.name = name
        self.thresholds = thresholds

    def evaluate(self, environment):
        result = {}
        for factor, ranges in self.thresholds.items():
            value = environment.get(factor)
            if value is None:
                continue
            for level, (low, high) in ranges.items():
                if low <= value <= high:
                    result[factor] = level
                    break
        return result


rules = [
    DiseaseRule("Asthma", {
        "humidity": {"emergency": (80, 100), "warning": (60, 79), "normal": (30, 59), "below normal": (0, 29)},
        "temperature": {"emergency": (35, 100), "warning": (30, 34), "normal": (20, 29), "below normal": (0, 19)},
        "noise_level": {"emergency": (80, 100), "warning": (60, 79), "normal": (30, 59), "below normal": (0, 29)},
    }),
    DiseaseRule("Migraine", {
        "illumination": {"emergency": (90, 100), "warning": (70, 89), "normal": (30, 69), "below normal": (0, 29)},
        "noise_level": {"emergency": (85, 100), "warning": (65, 84), "normal": (40, 64), "below normal": (0, 39)},
    }),
    DiseaseRule("Hypertension", {
        "temperature": {"emergency": (38, 100), "warning": (32, 37), "normal": (24, 31), "below normal": (0, 23)},
        "humidity": {"emergency": (80, 100), "warning": (65, 79), "normal": (40, 64), "below normal": (0, 39)},
    }),
    DiseaseRule("Flu", {
        "temperature": {"emergency": (0, 10), "warning": (11, 14), "normal": (15, 24), "below normal": (25, 100)},
        "humidity": {"emergency": (0, 20), "warning": (21, 39), "normal": (40, 60), "below normal": (61, 100)},
    }),
    DiseaseRule("Eczema", {
        "humidity": {"emergency": (0, 20), "warning": (21, 39), "normal": (40, 60), "below normal": (61, 100)},
        "temperature": {"emergency": (0, 10), "warning": (11, 15), "normal": (16, 30), "below normal": (31, 100)},
    }),
    DiseaseRule("Arthritis", {
        "temperature": {"emergency": (0, 5), "warning": (6, 10), "normal": (11, 25), "below normal": (26, 100)},
        "humidity": {"emergency": (80, 100), "warning": (60, 79), "normal": (30, 59), "below normal": (0, 29)},
    }),
    DiseaseRule("Heatstroke", {
        "temperature": {"emergency": (40, 100), "warning": (35, 39), "normal": (25, 34), "below normal": (0, 24)},
        "illumination": {"emergency": (90, 100), "warning": (70, 89), "normal": (30, 69), "below normal": (0, 29)},
    }),
    DiseaseRule("Cold Allergy", {
        "temperature": {"emergency": (0, 5), "warning": (6, 10), "normal": (11, 20), "below normal": (21, 100)},
    }),
    DiseaseRule("Sinusitis", {
        "humidity": {"emergency": (90, 100), "warning": (70, 89), "normal": (40, 69), "below normal": (0, 39)},
        "temperature": {"emergency": (0, 10), "warning": (11, 15), "normal": (16, 25), "below normal": (26, 100)},
    }),
    DiseaseRule("Allergy", {
        "humidity": {"emergency": (80, 100), "warning": (60, 79), "normal": (30, 59), "below normal": (0, 29)},
        "illumination": {"emergency": (90, 100), "warning": (70, 89), "normal": (40, 69), "below normal": (0, 39)},
    }),
]

environment = {
    "temperature": 36,
    "humidity": 75,
    "illumination": 85,
    "noise_level": 65
}

for rule in rules:
    print(rule.name, rule.evaluate(environment))

