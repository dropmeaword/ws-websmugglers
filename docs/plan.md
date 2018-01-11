## Day 1

11.45. Introductions
    - when do you normally have breaks?
    - what do you study?
    - on the 26/27 I come again to give another workshop, will it be for this same group?
    - if it's no for this group what do you know about the other group?
    - is anybody currently doing any project?
    - did you get clasess from Jon?
    - what have you been doing with Helena so far?
    - hwat is your research assignment/project about?
    - are you interested in pogramming? why?
    - is programming easy for you?
    - has anybody done any Arduino programming before?
    - what have you programmed so far?
    - have you touched upon internet protocols? what protocols?

    - I am quite fast and information dense, stop me any time for questions

    - what we are going to do in this workshop
        - a tiny version of the internet
        - a distributed web
        - an embodied website
        - a website smuggling device 

(shall I show some of the work I do with my other students?)

12.30 ESP8266
    - get one of this
    - what do you see?
    - what is it?
    - what do you think this is for?
    - how is this different from an Arduino?

13.00 programming the ESP8266
    - ways of programming the ESP8266
    - micropython: what is it?
    - getting our computer ready to flash the Wemos
    - flashing the firmware
    - loading micropython into the Wemos D1 mini Pro
    - interacting with the board through micropython code using the serial REPL

14.00 working with python directly on the board
    - interacting with the board through micropython code using the serial REPL
    - enabling the webREPL
    - listing files in the board's filesystem, what do you see?
    - this thing can hold files, unlike Arduino, why is that?
    - WiFi:
        - connecting to wifi as a client
        - scanning for available networks
        - different WiFi modes
        - making an access point
        - connect your laptop to the access point
        - looking at the IP you get from the
        - getting the board's networking details
        - IP, subnet, gateway, DNS server what is each of them?
    - adding your smuggler-board to the routers configuration and giving each a domain
    - pinging each board


15.00 building a tiny webserver
    - what is a server? how does it look like?
    - what does a server do?
    - what is a webserver? and what does it do?
    - can one webserver have more than one website?
    - opening a socket in micropython
    - binding to socket on port 80
    - what is 0.0.0.0?
    - listening forever
    - HTTP request/response RFC2616
        - what do they look like?
        - what is 404?
        - what is 200?
    - sending back a 200 success page with a message in the body
    - printing the request
    - observing the request, what it is? what information does it 'leak'?
    - understanding the request
    - what's the URL?
    - what does the URL correspond to in the server?
    - exercise: building your own parse/router
    - serving the first page ever on the web

16.00. A short talk about retro-web Geocities and some cases of censorship 
17.00. Design challenge: becoming a  website smuggler
    - where to kickstart your research?




# Day 2

(*) depending on the tempo of the class we might leave these topics for the second day
Saturday 9.45h to 17.30h
10.00. Brief concept presentations
11.00 - 17.00. Students make their “website smuggling wearable”
