import bottle
import datetime


global savednickname
savednickname = []
global savedproof
savedproof = []
global savedmessage
savedmessage = []
global savedtime
savedtime = []
global savedsubject
savedsubject = []
global savedbgrnd
savedbgrnd = 1

list = ["4242"]


def prettifydate(dt):
     return dt.strftime('%b %d %Y %H:%M:%S')


def listthree_to_html_dl(list3,list1,list2,list4):

     html='<dl>\n'
     cntr = 0

     while cntr < len(list1) and cntr < len(list2) and cntr < len(list3) and cntr < len(list4):
            html = html + '    <dt>Message Date: ' + list3[cntr] + '</dt>\n'
            html = html + '    <dt>Message Subject: ' + list4[cntr] + '</dt>\n'
            html = html + '    <dt>' + list1[cntr] + ' says: </dt>\n'
            html = html + '    <dd>' + list2[cntr] + '</dd>\n'
            cntr = cntr + 1

     html = html + '</dl>'
     return html

def listthree_to_html_dl1(list3,list1,list2,list4):

     html='<dl>\n'
     cntr = 0

     while cntr < len(list1) and cntr < len(list2) and cntr < len(list3) and cntr < len(list4):
            html = html + '    <dt>Message Date: ' + list3[cntr] + '</dt>\n'
            html = html + '    <dt>Message Subject: ' + list4[cntr] + '</dt>\n'
            html = html + '    <dt>' + list1[cntr] + ' says: </dt>\n'
            html = html + '    <dd>' + list2[cntr] + '</dd>\n'
            cntr = cntr + 1

     html = html + '</dl>'
     return html

def htmlify0(title, content):

    page = '<!DOCTYPE html>\n'
    page = page + '<html>\n'
    page = page + '  <head>\n'
    page = page + '    <title>' + title + '</title>\n'
    page = page + '    <link rel="stylesheet" type="text/css" href="static/mycss.css">\n'
    page = page + '    <meta charset="utf-8" />\n'
    page = page + '  </head>\n'
    page = page + '  <body>\n'
    page = page + '    ' + content + '\n'
    page = page + '  </body>\n'
    page = page + '</html>\n'
    return page

@bottle.route('/save',method='POST')
def save():

    global savedsubject
    tosavesubject = bottle.request.POST.get('savesubject')
    savedsubject = savedsubject + [tosavesubject]

    global savednickname
    tosavenickname = bottle.request.POST.get('savenickname')
    savednickname = savednickname + [tosavenickname]

    global savedmessage
    tosavemessage = bottle.request.POST.get('savemessage')
    savedmessage = savedmessage + [tosavemessage]

    global savedtime
    now = datetime.datetime.now()
    result3 = prettifydate(now)
    savedtime = savedtime + [result3]

    global savedbgrnd
    savedbgrnd = bottle.request.POST.get('bgrnd')



    return htmlify0('Your message has been saved !','''<h2>Your message has been received properly.</h2><hr><br>
                   <div><a href="/show">Click here to see your message.</a></div>''')


@bottle.route("/mainmenu")
def mainmenu():

    return htmlify0('Welcome to Can Community Website','''
    <div><h1>Welcome to Can Community Website</h1>
    <hr><h2>You can start sending messages to community easily.</h2>
    <form action="/save" method="post">
    <fieldset>
    <legend>Enter your Nickname and Message</legend>
    <p>Your nickname:</p>
    <input type="text" name="savenickname" />
    <p> Subject of Message:</p>
    <input type="text" name="savesubject" />
    <p> Your message:</p>
    <input type="text" name="savemessage" />
    <br>
    <p>You can go to Message Box with different colours</p>
    <input type="radio" name="bgrnd" value="default" checked>Default
    <br>
    <input type="radio" name="bgrnd" value="wood">Wood
    <br>
    <input type="radio" name="bgrnd" value="darkblue">Dark Blue
    <br><br>
    <input type="submit" value="Let's Go"></fieldset>
    </form>
    <br><br>
    <a href="/show">Click here to see the Messagebox.</a></div>
    ''')

@bottle.route('/')
def root():

    return htmlify0('Welcome to Can Communtity Website','''<div>
    <h1 class="1">Welcome to Can Community Website</h1>
    <hr>
    <h2>You can start sending messages to community easily.</h2>
    <form action="/saveproof" method="post">
    <fieldset>
    <legend>Please prove us that you are not a robot</legend>
    <p>Please enter the number (4242):</p>
    <input type="text" name="saveproof" />
    <br><input type="submit" value="Enter the Community" />
    </fieldset></form></div>'''
    )

@bottle.route("/show")
def show():

      global savednickname
      global savedmessage
      global savedtime
      global savedsubject
      global savedbgrnd

      result = listthree_to_html_dl(savedtime,savednickname,savedmessage,savedsubject)
      result1 = listthree_to_html_dl1(savedtime,savednickname,savedmessage,savedsubject)

      if savedbgrnd == "default":
        return '''<!DOCTYPE html><html><head><title>The MessageBox</title>
        <meta charset="utf-8"><link rel="stylesheet" type="text/css" href="static/style.css"></head>
        <body><div><h2>The Messagebox</h2><hr>''' + result1 + '''</div>
        <div><a href="/mainmenu">Click here to send more messages.</a></div></body>'''


      if savedbgrnd == "wood":
        return '''<!DOCTYPE html><html><head><title>The MessageBox</title>
        <meta charset="utf-8"><link rel="stylesheet" type="text/css" href="static/mycss.css"></head>
        <body class="rusticwoodbody" id="rusticwoodbody"><div><h2>The Messagebox</h2><hr>''' + result + '''
        </div><div><a href="/mainmenu">Click here to send more messages.</a></div></body></html>'''

      if savedbgrnd == "darkblue":
        return '''<!DOCTYPE html><html><head><title>The MessageBox</title>
        <meta charset="utf-8"><link rel="stylesheet" type="text/css" href="static/mycss.css"></head>
        <body class="darkbluebody"><div><h2>The Messagebox</h2><hr>''' + result + '''</div>
        <div><a href="/mainmenu">Click here to send more messages.</a></div></body></html>'''


@bottle.route('/saveproof',method='POST')
def saveproof():

    global savedproof
    tosaveproof = bottle.request.POST.get('saveproof')
    savedproof = [tosaveproof]


    if savedproof == list:
        return htmlify0('You can access to Community!','<h2>You are allowed to enter the Community</h2><hr><br><div><a href="/mainmenu">Click here to access to Community</a></div>')

    else:
        return htmlify0('Are you human ?','<h2>Something went wrong</h2><hr><br>We are not sure that you are human. <a href="/">Please prove us that you are human</a>')

@bottle.route("/static/<filename>")
def mycss(filename):

    return bottle.static_file(filename, root = "/home/canaltinigne/mysite/static/")

application = bottle.default_app()
