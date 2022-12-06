import os
import sys
from flask import *
from api_photos import *
import json


app = Flask(__name__)

@app.route('/', methods=['GET'])
def index():
    if request.method == 'GET':
        albums = get_albums()
        first = first_in_album()
        return render_template('index.html', albums=albums, first=first)
    elif request.method == 'POST':
        albums = request.form['name']
        return render_template('album.html', albums=albums)


@app.route('/album/<album>', methods=['GET', 'POST'])
def album(album):
    if request.method == 'GET':
        print(album)
        photos = get_photos(album)
        print(photos)
        return render_template('album.html', photos=photos, album=album)
    elif request.method == 'POST':
        albums = request.form['name']
        return render_template('album.html', albums=albums)
    return render_template('album.html')

@app.route('/Library', methods=['GET', 'POST'])
def library():
    if request.method == 'GET':
        photos = get_all_photos()
        return render_template('library.html', photos=photos)
    return render_template('Library.html')

@app.route('/add_photo', methods=['GET', 'POST'])
def add():
    if request.method == 'GET':
        return render_template('add.html')
    elif request.method == 'POST':
        photos = request.files.getlist('file')
        album = request.form['name']
        f = open('static/albums/' + album + '.json', 'w')
        f.write('[]')
        f.close()
        for photo in photos:
            photo.save(os.path.join('static/images', photo.filename))
            os.system('./api.o ' + album + ' ' +
                      'static/images/' + photo.filename)
        return redirect(url_for('index'))
    return render_template('add.html')

if __name__ == '__main__':
    app.run(debug=True, port=80, host='0.0.0.0')
