import re
import string
import json

with open('dictionary.json', "r") as a:
    data = json.load(a)
    with open('dictionary_a.json', "w") as f:
        for key in data:
            # We have the definition, now we need to split the definition up by
            # regex "%d." and then store the results as a list replacing the current value
            definitions = re.split("\d\.", data[key])
            all_senses = []
            for definition in definitions:
                clean_definition = re.sub('[^A-Za-z0-9]+', ' ', definition)
                clean_definition = clean_definition.strip()
                if clean_definition == "":
                    continue
                all_senses.append(clean_definition)
            data[key] = all_senses
        json_string = json.dumps(data, default=lambda o: o.__dict__, sort_keys=True, indent=2)
        f.write(json_string)
