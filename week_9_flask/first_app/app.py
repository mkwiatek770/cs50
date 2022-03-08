from flask import Flask, render_template, request

# turn this file into flask application
app = Flask(__name__)


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/greet', methods=['POST'])
def greet():
    name = name = request.form.get('name', 'anonymous person')
    return render_template('greet.html', name=name)
