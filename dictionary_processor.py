import re
import string
import json

characters = ['-', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
              'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

def break_up_definitions():
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


def break_up_dictionary_by_characters():
    with open('dictionary.json', "r") as curr_dic:
        data = json.load(curr_dic)
        last_char = "-"
        f = open(last_char + ".json", "w")
        curr_letter_dictionary = {}
        for key in data:
            if key[0] != "-" and key[0] != last_char:
                json_string = json.dumps(curr_letter_dictionary, sort_keys=True, separators=(',', ':'))
                f.write(json_string)
                f.close()
                curr_letter_dictionary = {}
                last_char = key[0]
                f = open(last_char + ".json", "w")
            curr_letter_dictionary[key] = data[key]
        json_string = json.dumps(curr_letter_dictionary, sort_keys=True, separators=(',', ':'))
        f.write(json_string)
        f.close()


def main():
    break_up_dictionary_by_characters()

if __name__ == '__main__':
    main()