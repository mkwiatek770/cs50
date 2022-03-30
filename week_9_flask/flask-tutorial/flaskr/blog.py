from flask import Blueprint
from flask import flash
from flask import g
from flask import redirect
from flask import render_template
from flask import request
from flask import url_for
from werkzeug.exceptions import abort

from flaskr.auth import login_required
from flaskr.db import get_db

bp = Blueprint('blog', __name__)


@bp.route('/')
def index():
    db = get_db()
    posts = db.execute(
        'SELECT p.id, title, body, created, author_id, username '
        'FROM post p JOIN user u ON p.author_id = u.id '
        'ORDER BY created DESC'
    ).fetchall()
    return render_template('blog/index.html', posts=posts)


@bp.route('/create', methods=('GET', 'POST'))
@login_required
def create():
    if request.method == 'POST':
        db = get_db()
        title = request.form['title']
        body = request.form['body']
        author_id = g.user['id']

        if title == '':
            flash('Title can`t be empty')
    
        db.execute(
            'INSERT INTO post (author_id, title, body) '
            'VALUES (?, ?, ?)',
            (author_id, title, body)
        )
        db.commit()
        return redirect(url_for('blog.index'))
    return render_template('blog/create.html')


@bp.route('/<int:id>/update', methods=('GET', 'POST'))
@login_required
def update(id):
    post = get_post(id)

    if request.method == 'POST':
        title = request.form['title']
        body = request.form['body']
        error = None

        if not title:
            error = 'Title is required.'
        
        if error is not None:
            flash(error)
        else:
            db = get_db()
            db.execute(
                'UPDATE post SET title = ?, body = ? '
                'WHERE id = ?',
                (title, body, id,)
            )
            db.commit()
            flash('Updated.')
            return redirect(url_for('blog.index'))
    return render_template('blog/update.html', post=post)


@bp.route('/<int:id>/delete', methods=('POST',))
@login_required
def delete(id):
    get_post(id, check_author=True)
    db = get_db()

    try:
        db.execute('DELETE FROM post WHERE id = ?', (id,))
        db.commit()
        flash('Deleted.')
    except db.IntegrityError:
        flash(f'Post with id={id} doesn`t exist.')
    return redirect(url_for('blog.index'))


def get_post(id, check_author=True):
    post = get_db().execute(
        'SELECT p.id, title, body, created, author_id, username '
        'FROM post p JOIN user u ON p.author_id = u.id '
        'WHERE p.id = ?',
        (id,)
    ).fetchone()

    if post is None:
        abort(404, f'Post with id={id} doesn`t exist.')
    if check_author and post['author_id'] != g.user['id']:
        abort(403)  # Forbidden
    
    return post
 