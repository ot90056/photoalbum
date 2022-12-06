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
        request.form['album']
        return redirect(url_for('album', album=request.form['album'], photos=get_photos(request.form['album'])))


@app.route('/album', methods=['GET', 'POST'])
def Albums(album):
    if request.method == 'GET':
        print(album)
        photos = get_photos(album)
        return render_template('album.html', photos=photos, album=album)

    elif request.method == 'POST':
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
        photos = request.files.getlist('photo')
        album = request.form['name']
        for photo in photos:
            photo.save(os.path.join('static/images', photo.filename))
            with open('static/albums/' + album, 'a') as f:
                f.write(json.dumps({'location': 'static/images/' + photo.filename}))
        return redirect(url_for('index'))
    return render_template('add.html')

if __name__ == '__main__':
    app.run(debug=True, port=80, host='0.0.0.0')
