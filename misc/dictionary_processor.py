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


"""
Go through every key in the dictionary
If the length is one, create a key with a dictionary with the same key-value pair inside.
Else
Check if the first + second letter key exists in dictionary. If not, then create one and add the curr key value pair.
      else add the keyvalue pair in the existing first+second letter key dictionary.

Go through every key and create a file for them

"""

def break_up_dictionary_by_characters():
    with open('dictionary.json', "r") as curr_dic:
        data = json.load(curr_dic)

        files_dictionary = {}
        for key in data:
            if len(key) == 1:
                files_dictionary[key] = {key:data[key]}
            else:
                if (key[0] + key[1]) not in files_dictionary:
                    files_dictionary[key[0] + key[1]] = {key:data[key]}
                else:
                    files_dictionary[key[0] + key[1]][key] = data[key]

        for key in files_dictionary:
            f = open(key + ".json", "w")
            json_string = json.dumps(files_dictionary[key], sort_keys=True, separators=(',', ':'))
            f.write(json_string)
            f.close()


def main():
    break_up_dictionary_by_characters()

if __name__ == '__main__':
    main()