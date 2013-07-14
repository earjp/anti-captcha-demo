import urllib
import urllib2

def write_file(file, s):
    f=open(file, 'wb')
    f.write(s)
    f.close()

def save_image(i):
    url = "https://secure.bilibili.tv/captcha"
    user_agent = 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'
    values = {}
    headers = { 'User-Agent' : user_agent }
    data = urllib.urlencode(values)
    req = urllib2.Request(url, data, headers)
    try:
        response=urllib2.urlopen(req, timeout = 10)
        a = response.read()
        write_file('downloadCAPTCHA/Image%03d.png'%i, a)
    except Exception, e:
        print "ERROR,rerun later...", e
        save_image(i)
    else:
        print "Complete: ",i

for i in range(1, 301):
    print 'Starting:',i
    save_image(i)
