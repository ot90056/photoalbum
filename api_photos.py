import json
import os
import sys

def first_in_album():
    first_in_album = []
    for album in os.listdir('static/albums'):
        with open('static/albums/' + album) as f:
            data = json.load(f)            
            first_in_album.append(data[0]['location'])
    return first_in_album

def get_albums():
    albums = []
    for album in os.listdir('static/albums'):
        albums.append(album)
    return albums

def get_all_photos():
    photos = []
    for album in os.listdir('static/images'):
        photos.append("static/images/"+album)
    return photos

def get_photos(album):
    photos = []
    with open('static/albums/' + album) as f:
        data = json.load(f)
        for photo in data:
            photos.append(photo['location'])
    return photos


def get_album():
    pass