import requests
import json

### Requesting data from site, and converting json to python dict
data = requests.get('https://api.ampifymusic.com/packs')
y = json.loads(data.text)

### Creating a dictionary with packs sorted by genre
packsByGenre = {}
for pack in y['packs']:
	for genre in pack['genres']:
		packsByGenre.setdefault(genre, [])
	packsByGenre[genre].append(pack['name'])

### Printing all unique genres ie. keys in packsByGenre dictionary
print('List of all unique genres: \n')
genres = list(packsByGenre.keys())
genres.sort()
print(genres)
print('\n')

### Chosen genre to print
genre = 'hip-hop'

print("List of all the packs in the genre '{}': \n".format(genre))
print(packsByGenre[genre])