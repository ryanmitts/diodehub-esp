const char HTTP_HEAD[] PROGMEM            = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\"content=\"width=device-width,initial-scale=1,user-scalable=no\"/><title>{v}</title>";
const char HTTP_STYLE[] PROGMEM           = "<style> :root{ /*CSS VARIABLE THEME COLOR*/ /*--primarycolor:#9933CC;*/ --primarycolor:#558EF8; }body.invert,body.invert a,body.invert h1{ background-color:#060606;color:white; }body.invert.msg{background-color: #282828;border-top:1px solid#555;border-right:1px solid#555;border-bottom:1px solid#555;color:#fff; }body.invert.q[role=img] { -webkit-filter:invert(1);filter:invert(1); } .c,body{ text-align:center;font-family:verdana;margin:0; } .wrap{ text-align:left;display:inline-block;min-width:260px;max-width:500px; }div,input{ padding:5px;font-size:1em; /*width:100%;*/margin:5px 0;box-sizing:border-box; }input,button,.msg{width:100%; }button,input[type=\"button\"],input[type=\"submit\"] {border:0;background-color:var(--primarycolor);color: #fff;line-height:2.4rem;font-size:1.2rem;cursor:pointer;outline:none; }button:hover,input[type=\"button\"]:hover,input[type=\"submit\"]:hover{ filter:brightness(0.9); }input[type=\"file\"]{border:1px solid var(--primarycolor); }a {color: #000;font-weight:700;text-decoration:none; }a:hover{ color:var(--primarycolor);text-decoration:underline; } .h{ display:none; } .q{ height:16px;margin:0;padding:0 5px;text-align:right;min-width:38px;float:right; } .q.q-0:after{ background-position-x:0; } .q.q-1:after{ background-position-x: -16px; } .q.q-2:after{ background-position-x: -32px; } .q.q-3:after{ background-position-x: -48px; } .q.q-4:after{ background-position-x: -64px; } .q.l:before{ background-position-x: -80px;padding-right:5px} .ql.q{ float:left; } .q:after, .q:before{ content: '';width:16px;height:16px;display:inline-block;background-repeat:no-repeat;background-position:16px 0;background-image:url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAAAQCAMAAADeZIrLAAAAJFBMVEX///8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADHJj5lAAAAC3RSTlMAIjN3iJmqu8zd7vF8pzcAAABsSURBVHja7Y1BCsAwCASNSVo3/v+/BUEiXnIoXkoX5jAQMxTHzK9cVSnvDxwD8bFx8PhZ9q8FmghXBhqA1faxk92PsxvRc2CCCFdhQCbRkLoAQ3q/wWUBqG35ZxtVzW4Ed6LngPyBU2CobdIDQ5oPWI5nCUwAAAAASUVORK5CYII='); } @media(-webkit-min-device-pixel-ratio:2), (min-resolution:192dpi) { .q:before, .q:after{ background-image:url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAALwAAAAgCAMAAACfM+KhAAAALVBMVEX///8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADAOrOgAAAADnRSTlMAESIzRGZ3iJmqu8zd7gKjCLQAAACmSURBVHgB7dDBCoMwEEXRmKlVY3L//3NLhyzqIqSUggy8uxnhCR5Mo8xLt+14aZ7wwgsvvPA/ofv9+44334UXXngvb6XsFhO/VoC2RsSv9J7x8BnYLW+AjT56ud/uePMdb7IP8Bsc/e7h8Cfk912ghsNXWPpDC4hvN+D1560A1QPORyh84VKLjjdvfPFm++i9EWq0348XXnjhhT+4dIbCW+WjZim9AKk4UZMnnCEuAAAAAElFTkSuQmCC');background-size:95px 16px; } } .msg{ padding:20px;margin:20px 0;border:1px solid#eee;border-left-width:5px;border-left-color: #777; } .msg h4{ margin-top:0;margin-bottom:5px; } .msg.P{ border-left-color:var(--primarycolor); } .msg.P h4{ color:var(--primarycolor); } /*.msg.S{ border-left-color: #5cb85c; } .msg.S h4{ color: #5cb85c; }*/ .msg.D{ border-left-color: #dc3630; } .msg.D h4{ color: #dc3630; }dt{ font-weight:bold; }dd{ margin:0;padding:0 0 0.5em 0; }td{ vertical-align:top; }button.D{background-color:#dc3630; } .header{ width:100%;background-color: #24252a;padding:8px;margin:0;height:64px;display:flex;align-items:middle;box-shadow:0px 2px 4px-1px rgba(0,0,0,0.2),0px 4px 5px 0px rgba(0,0,0,0.14),0px 1px 10px 0px rgba(0,0,0,0.12); } .logo-link{ display:flex; } .logo{ width:10rem;margin-left:8px; } </style>";
const char HTTP_SCRIPT[] PROGMEM          = "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();} </script>";
const char HTTP_HEAD_END[] PROGMEM        = "</head><body><div class='header'><a class='logo-link'href='/'><img class='logo'src='/logo.svg'></a></div><div class='wrap'><!-- <div class='wrap ql qinv'> -->";
const char SAMPLE[] PROGMEM               = "<h2>/</h2><hR><!-- /SAMPLE--><!--HTTP_PORTAL_OPTIONS--><!-- /HTTP_PORTAL_OPTIONS--><!--HTTP_PORTAL_MENU[] --><form action='/wifi'method='get'><button>Configure WiFi</button></form><br/><form action='/0wifi'method='get'><button>Configure WiFi(No Scan)</button></form><br/><form action='/info'method='get'><button>Info</button></form><br/><form action='/param'method='get'><button>Setup</button></form><br/><Hr><br/><form action='/close'method='post'><button>Close</button></form><br/><form action='/erase'method='post'><button class='D'>Erase</button></form><br/><form action='/restart'method='post'><button>Restart</button></form><br/><form action='/exit'method='post'><button>Exit</button></form><br/><!-- /HTTP_PORTAL_MENU--><!--SAMPLE--><h2>/wifi</h2><hr><div><a href='#p'onclick='c(this)'>Acccess Point 01</a><div role='img'aria-label='88%'title='88%'class='q q-4 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 02</a><div role='img'aria-label='88%'title='88%'class='q q-4'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 03</a><div role='img'aria-label='60%'title='60%'class='q q-3 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 04</a><div role='img'aria-label='60%'title='60%'class='q q-3'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 05</a><div role='img'aria-label='60%'title='60%'class='q q-3'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 06</a><div role='img'aria-label='40%'title='40%'class='q q-2'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 07</a><div role='img'aria-label='40%'title='40%'class='q q-2 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 08</a><div role='img'aria-label='20%'title='20%'class='q q-1'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 09</a><div role='img'aria-label='20%'title='20%'class='q q-1'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 10</a><div role='img'aria-label='20%'title='20%'class='q q-4 l'></div><div class='q'>100%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 11</a><div role='img'aria-label='10%'title='10%'class='q q-3'></div><div class='q'>70%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 12</a><div role='img'aria-label='10%'title='10%'class='q q-1 l'></div><div class='q'>10%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 13</a><div role='img'aria-label='10%'title='10%'class='q q-0 h'></div><div class='q'>100%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 14</a><div class='q'>66%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 15</a><div class='q'>56%</div></div><!-- /SAMPLE--><!--HTTP_ITEM--><div><a href='#p'onclick='c(this)'>{v}</a><div role='img'aria-label='{r}%'title='{r}%'class='q q-{q} {i}'></div></div><!-- /HTTP_ITEM--><!--HTTP_FORM_START--><form method='get'action='wifisave'><label for='s'>SSID</label><br/><input id='s'name='s'length=32 placeholder='SSID'><br/><label for='p'>Password</label><input id='p'name='p'length=64 type='password'placeholder='password'><br/><!-- /HTTP_FORM_START--><!--SAMPLE--><h3>custom parameter</h3><hr><br/><label for='custom'>Label for Custom Param</label><br/><input id='custom'name='custom'length='255'placeholder='placeholder'value='' {c}><!-- /SAMPLE--><!--HTTP_FORM_LABEL--><br/><label for='{i}'>{p}</label><!-- /HTTP_FORM_LABEL--><!--HTTP_FORM_PARAM--><br/><input id='{i}'name='{n}'length='{l}'placeholder='{p}'value='{v}' {c}><!-- /HTTP_FORM_PARAM--><!--HTTP_FORM_END--><br/><button type='submit'>Save</button></form><!-- /HTTP_FORM_END--><!--HTTP_SCAN_LINK--><br/><form action='/wifi'method='get'><button>Refresh</button></form><!-- /HTTP_SCAN_LINK--><!--HTTP_SAVED--><div class='msg'><h4>Saving Credentials</h4>Trying to connect ESP to network.<br/>If it fails reconnect to AP to try again</div><!-- /HTTP_SAVED--><!--HTTP_STATUS_ON--><div class='msg P'><strong>Connected</strong>to{v}<br/><em><small>with IP{i}</small></em></div><!-- /HTTP_STATUS_ON--><!--HTTP_STATUS_OFF--><div class='msg{c}'><strong>Not Connected</strong>to{v}{r}</div><!-- /HTTP_STATUS_OFF--><!--sample--><div class='msg D'><strong>Not Connected</strong>to apname<!-- /sample--><!--HTTP_STATUS_OFFPW--><br/>Authentication Failure<!-- /HTTP_STATUS_OFFPW--><!--HTTP_STATUS_OFFNOAP--><br/>AP not found<!-- /HTTP_STATUS_OFFNOAP--><!--HTTP_STATUS_OFFFAIL--><br/>Could not Connect<!-- /HTTP_STATUS_OFFFAIL--></div><!--HTTP_STATUS_NONE--><div class='msg'>No AP set</div><!-- /HTTP_STATUS_NONE--><!--SAMPLE--><div class='msg P'><h4>H4 Color Header</h4>content</div><!-- /SAMPLE--><!--SAMPLE--><h2>/info</h3><hr><dl><dt>Chip ID</dt><dd>123456</dd><dt>Flash Chip ID</dt><dd>1234556</dd><dt>IDE Flash Size</dt><dd>4194304 bytes</dd><dt>Real Flash Size</dt><dd>4194304 bytes</dd><dt>Empty</dt><dd></dd><dt>Soft AP IP</dt><dd>192.168.4.1</dd><dt>Soft AP MAC</dt><dd>00:00:00:00:00:00</dd><dt>Station MAC</dt><dd>00:00:00:00:00:00</dd></dl>";
const char HTTP_PORTAL_OPTIONS[] PROGMEM  = "";
const char SAMPLE[] PROGMEM               = "<h2>/</h2><hR><!-- /SAMPLE--><!--HTTP_PORTAL_OPTIONS--><!-- /HTTP_PORTAL_OPTIONS--><!--HTTP_PORTAL_MENU[] --><form action='/wifi'method='get'><button>Configure WiFi</button></form><br/><form action='/0wifi'method='get'><button>Configure WiFi(No Scan)</button></form><br/><form action='/info'method='get'><button>Info</button></form><br/><form action='/param'method='get'><button>Setup</button></form><br/><Hr><br/><form action='/close'method='post'><button>Close</button></form><br/><form action='/erase'method='post'><button class='D'>Erase</button></form><br/><form action='/restart'method='post'><button>Restart</button></form><br/><form action='/exit'method='post'><button>Exit</button></form><br/><!-- /HTTP_PORTAL_MENU--><!--SAMPLE--><h2>/wifi</h2><hr><div><a href='#p'onclick='c(this)'>Acccess Point 01</a><div role='img'aria-label='88%'title='88%'class='q q-4 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 02</a><div role='img'aria-label='88%'title='88%'class='q q-4'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 03</a><div role='img'aria-label='60%'title='60%'class='q q-3 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 04</a><div role='img'aria-label='60%'title='60%'class='q q-3'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 05</a><div role='img'aria-label='60%'title='60%'class='q q-3'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 06</a><div role='img'aria-label='40%'title='40%'class='q q-2'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 07</a><div role='img'aria-label='40%'title='40%'class='q q-2 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 08</a><div role='img'aria-label='20%'title='20%'class='q q-1'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 09</a><div role='img'aria-label='20%'title='20%'class='q q-1'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 10</a><div role='img'aria-label='20%'title='20%'class='q q-4 l'></div><div class='q'>100%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 11</a><div role='img'aria-label='10%'title='10%'class='q q-3'></div><div class='q'>70%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 12</a><div role='img'aria-label='10%'title='10%'class='q q-1 l'></div><div class='q'>10%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 13</a><div role='img'aria-label='10%'title='10%'class='q q-0 h'></div><div class='q'>100%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 14</a><div class='q'>66%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 15</a><div class='q'>56%</div></div><!-- /SAMPLE--><!--HTTP_ITEM--><div><a href='#p'onclick='c(this)'>{v}</a><div role='img'aria-label='{r}%'title='{r}%'class='q q-{q} {i}'></div></div><!-- /HTTP_ITEM--><!--HTTP_FORM_START--><form method='get'action='wifisave'><label for='s'>SSID</label><br/><input id='s'name='s'length=32 placeholder='SSID'><br/><label for='p'>Password</label><input id='p'name='p'length=64 type='password'placeholder='password'><br/><!-- /HTTP_FORM_START--><!--SAMPLE--><h3>custom parameter</h3><hr><br/><label for='custom'>Label for Custom Param</label><br/><input id='custom'name='custom'length='255'placeholder='placeholder'value='' {c}><!-- /SAMPLE--><!--HTTP_FORM_LABEL--><br/><label for='{i}'>{p}</label><!-- /HTTP_FORM_LABEL--><!--HTTP_FORM_PARAM--><br/><input id='{i}'name='{n}'length='{l}'placeholder='{p}'value='{v}' {c}><!-- /HTTP_FORM_PARAM--><!--HTTP_FORM_END--><br/><button type='submit'>Save</button></form><!-- /HTTP_FORM_END--><!--HTTP_SCAN_LINK--><br/><form action='/wifi'method='get'><button>Refresh</button></form><!-- /HTTP_SCAN_LINK--><!--HTTP_SAVED--><div class='msg'><h4>Saving Credentials</h4>Trying to connect ESP to network.<br/>If it fails reconnect to AP to try again</div><!-- /HTTP_SAVED--><!--HTTP_STATUS_ON--><div class='msg P'><strong>Connected</strong>to{v}<br/><em><small>with IP{i}</small></em></div><!-- /HTTP_STATUS_ON--><!--HTTP_STATUS_OFF--><div class='msg{c}'><strong>Not Connected</strong>to{v}{r}</div><!-- /HTTP_STATUS_OFF--><!--sample--><div class='msg D'><strong>Not Connected</strong>to apname<!-- /sample--><!--HTTP_STATUS_OFFPW--><br/>Authentication Failure<!-- /HTTP_STATUS_OFFPW--><!--HTTP_STATUS_OFFNOAP--><br/>AP not found<!-- /HTTP_STATUS_OFFNOAP--><!--HTTP_STATUS_OFFFAIL--><br/>Could not Connect<!-- /HTTP_STATUS_OFFFAIL--></div><!--HTTP_STATUS_NONE--><div class='msg'>No AP set</div><!-- /HTTP_STATUS_NONE--><!--SAMPLE--><div class='msg P'><h4>H4 Color Header</h4>content</div><!-- /SAMPLE--><!--SAMPLE--><h2>/info</h3><hr><dl><dt>Chip ID</dt><dd>123456</dd><dt>Flash Chip ID</dt><dd>1234556</dd><dt>IDE Flash Size</dt><dd>4194304 bytes</dd><dt>Real Flash Size</dt><dd>4194304 bytes</dd><dt>Empty</dt><dd></dd><dt>Soft AP IP</dt><dd>192.168.4.1</dd><dt>Soft AP MAC</dt><dd>00:00:00:00:00:00</dd><dt>Station MAC</dt><dd>00:00:00:00:00:00</dd></dl>";
const char HTTP_ITEM[] PROGMEM            = "<div><a href='#p'onclick='c(this)'>{v}</a><div role='img'aria-label='{r}%'title='{r}%'class='q q-{q} {i}'></div></div>";
const char HTTP_FORM_START[] PROGMEM      = "<form method='get'action='wifisave'><label for='s'>SSID</label><br/><input id='s'name='s'length=32 placeholder='SSID'><br/><label for='p'>Password</label><input id='p'name='p'length=64 type='password'placeholder='password'><br/>";
const char SAMPLE[] PROGMEM               = "<h2>/</h2><hR><!-- /SAMPLE--><!--HTTP_PORTAL_OPTIONS--><!-- /HTTP_PORTAL_OPTIONS--><!--HTTP_PORTAL_MENU[] --><form action='/wifi'method='get'><button>Configure WiFi</button></form><br/><form action='/0wifi'method='get'><button>Configure WiFi(No Scan)</button></form><br/><form action='/info'method='get'><button>Info</button></form><br/><form action='/param'method='get'><button>Setup</button></form><br/><Hr><br/><form action='/close'method='post'><button>Close</button></form><br/><form action='/erase'method='post'><button class='D'>Erase</button></form><br/><form action='/restart'method='post'><button>Restart</button></form><br/><form action='/exit'method='post'><button>Exit</button></form><br/><!-- /HTTP_PORTAL_MENU--><!--SAMPLE--><h2>/wifi</h2><hr><div><a href='#p'onclick='c(this)'>Acccess Point 01</a><div role='img'aria-label='88%'title='88%'class='q q-4 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 02</a><div role='img'aria-label='88%'title='88%'class='q q-4'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 03</a><div role='img'aria-label='60%'title='60%'class='q q-3 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 04</a><div role='img'aria-label='60%'title='60%'class='q q-3'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 05</a><div role='img'aria-label='60%'title='60%'class='q q-3'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 06</a><div role='img'aria-label='40%'title='40%'class='q q-2'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 07</a><div role='img'aria-label='40%'title='40%'class='q q-2 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 08</a><div role='img'aria-label='20%'title='20%'class='q q-1'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 09</a><div role='img'aria-label='20%'title='20%'class='q q-1'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 10</a><div role='img'aria-label='20%'title='20%'class='q q-4 l'></div><div class='q'>100%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 11</a><div role='img'aria-label='10%'title='10%'class='q q-3'></div><div class='q'>70%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 12</a><div role='img'aria-label='10%'title='10%'class='q q-1 l'></div><div class='q'>10%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 13</a><div role='img'aria-label='10%'title='10%'class='q q-0 h'></div><div class='q'>100%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 14</a><div class='q'>66%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 15</a><div class='q'>56%</div></div><!-- /SAMPLE--><!--HTTP_ITEM--><div><a href='#p'onclick='c(this)'>{v}</a><div role='img'aria-label='{r}%'title='{r}%'class='q q-{q} {i}'></div></div><!-- /HTTP_ITEM--><!--HTTP_FORM_START--><form method='get'action='wifisave'><label for='s'>SSID</label><br/><input id='s'name='s'length=32 placeholder='SSID'><br/><label for='p'>Password</label><input id='p'name='p'length=64 type='password'placeholder='password'><br/><!-- /HTTP_FORM_START--><!--SAMPLE--><h3>custom parameter</h3><hr><br/><label for='custom'>Label for Custom Param</label><br/><input id='custom'name='custom'length='255'placeholder='placeholder'value='' {c}><!-- /SAMPLE--><!--HTTP_FORM_LABEL--><br/><label for='{i}'>{p}</label><!-- /HTTP_FORM_LABEL--><!--HTTP_FORM_PARAM--><br/><input id='{i}'name='{n}'length='{l}'placeholder='{p}'value='{v}' {c}><!-- /HTTP_FORM_PARAM--><!--HTTP_FORM_END--><br/><button type='submit'>Save</button></form><!-- /HTTP_FORM_END--><!--HTTP_SCAN_LINK--><br/><form action='/wifi'method='get'><button>Refresh</button></form><!-- /HTTP_SCAN_LINK--><!--HTTP_SAVED--><div class='msg'><h4>Saving Credentials</h4>Trying to connect ESP to network.<br/>If it fails reconnect to AP to try again</div><!-- /HTTP_SAVED--><!--HTTP_STATUS_ON--><div class='msg P'><strong>Connected</strong>to{v}<br/><em><small>with IP{i}</small></em></div><!-- /HTTP_STATUS_ON--><!--HTTP_STATUS_OFF--><div class='msg{c}'><strong>Not Connected</strong>to{v}{r}</div><!-- /HTTP_STATUS_OFF--><!--sample--><div class='msg D'><strong>Not Connected</strong>to apname<!-- /sample--><!--HTTP_STATUS_OFFPW--><br/>Authentication Failure<!-- /HTTP_STATUS_OFFPW--><!--HTTP_STATUS_OFFNOAP--><br/>AP not found<!-- /HTTP_STATUS_OFFNOAP--><!--HTTP_STATUS_OFFFAIL--><br/>Could not Connect<!-- /HTTP_STATUS_OFFFAIL--></div><!--HTTP_STATUS_NONE--><div class='msg'>No AP set</div><!-- /HTTP_STATUS_NONE--><!--SAMPLE--><div class='msg P'><h4>H4 Color Header</h4>content</div><!-- /SAMPLE--><!--SAMPLE--><h2>/info</h3><hr><dl><dt>Chip ID</dt><dd>123456</dd><dt>Flash Chip ID</dt><dd>1234556</dd><dt>IDE Flash Size</dt><dd>4194304 bytes</dd><dt>Real Flash Size</dt><dd>4194304 bytes</dd><dt>Empty</dt><dd></dd><dt>Soft AP IP</dt><dd>192.168.4.1</dd><dt>Soft AP MAC</dt><dd>00:00:00:00:00:00</dd><dt>Station MAC</dt><dd>00:00:00:00:00:00</dd></dl>";
const char HTTP_FORM_LABEL[] PROGMEM      = "<br/><label for='{i}'>{p}</label>";
const char HTTP_FORM_PARAM[] PROGMEM      = "<br/><input id='{i}'name='{n}'length='{l}'placeholder='{p}'value='{v}' {c}>";
const char HTTP_FORM_END[] PROGMEM        = "<br/><button type='submit'>Save</button></form>";
const char HTTP_SCAN_LINK[] PROGMEM       = "<br/><form action='/wifi'method='get'><button>Refresh</button></form>";
const char HTTP_SAVED[] PROGMEM           = "<div class='msg'><h4>Saving Credentials</h4>Trying to connect ESP to network.<br/>If it fails reconnect to AP to try again</div>";
const char HTTP_STATUS_ON[] PROGMEM       = "<div class='msg P'><strong>Connected</strong>to{v}<br/><em><small>with IP{i}</small></em></div>";
const char HTTP_STATUS_OFF[] PROGMEM      = "<div class='msg{c}'><strong>Not Connected</strong>to{v}{r}</div>";
const char HTTP_STATUS_OFFPW[] PROGMEM    = "<br/>Authentication Failure";
const char HTTP_STATUS_OFFNOAP[] PROGMEM  = "<br/>AP not found";
const char HTTP_STATUS_OFFFAIL[] PROGMEM  = "<br/>Could not Connect";
const char HTTP_STATUS_NONE[] PROGMEM     = "<div class='msg'>No AP set</div>";
const char SAMPLE[] PROGMEM               = "<h2>/</h2><hR><!-- /SAMPLE--><!--HTTP_PORTAL_OPTIONS--><!-- /HTTP_PORTAL_OPTIONS--><!--HTTP_PORTAL_MENU[] --><form action='/wifi'method='get'><button>Configure WiFi</button></form><br/><form action='/0wifi'method='get'><button>Configure WiFi(No Scan)</button></form><br/><form action='/info'method='get'><button>Info</button></form><br/><form action='/param'method='get'><button>Setup</button></form><br/><Hr><br/><form action='/close'method='post'><button>Close</button></form><br/><form action='/erase'method='post'><button class='D'>Erase</button></form><br/><form action='/restart'method='post'><button>Restart</button></form><br/><form action='/exit'method='post'><button>Exit</button></form><br/><!-- /HTTP_PORTAL_MENU--><!--SAMPLE--><h2>/wifi</h2><hr><div><a href='#p'onclick='c(this)'>Acccess Point 01</a><div role='img'aria-label='88%'title='88%'class='q q-4 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 02</a><div role='img'aria-label='88%'title='88%'class='q q-4'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 03</a><div role='img'aria-label='60%'title='60%'class='q q-3 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 04</a><div role='img'aria-label='60%'title='60%'class='q q-3'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 05</a><div role='img'aria-label='60%'title='60%'class='q q-3'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 06</a><div role='img'aria-label='40%'title='40%'class='q q-2'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 07</a><div role='img'aria-label='40%'title='40%'class='q q-2 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 08</a><div role='img'aria-label='20%'title='20%'class='q q-1'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 09</a><div role='img'aria-label='20%'title='20%'class='q q-1'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 10</a><div role='img'aria-label='20%'title='20%'class='q q-4 l'></div><div class='q'>100%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 11</a><div role='img'aria-label='10%'title='10%'class='q q-3'></div><div class='q'>70%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 12</a><div role='img'aria-label='10%'title='10%'class='q q-1 l'></div><div class='q'>10%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 13</a><div role='img'aria-label='10%'title='10%'class='q q-0 h'></div><div class='q'>100%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 14</a><div class='q'>66%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 15</a><div class='q'>56%</div></div><!-- /SAMPLE--><!--HTTP_ITEM--><div><a href='#p'onclick='c(this)'>{v}</a><div role='img'aria-label='{r}%'title='{r}%'class='q q-{q} {i}'></div></div><!-- /HTTP_ITEM--><!--HTTP_FORM_START--><form method='get'action='wifisave'><label for='s'>SSID</label><br/><input id='s'name='s'length=32 placeholder='SSID'><br/><label for='p'>Password</label><input id='p'name='p'length=64 type='password'placeholder='password'><br/><!-- /HTTP_FORM_START--><!--SAMPLE--><h3>custom parameter</h3><hr><br/><label for='custom'>Label for Custom Param</label><br/><input id='custom'name='custom'length='255'placeholder='placeholder'value='' {c}><!-- /SAMPLE--><!--HTTP_FORM_LABEL--><br/><label for='{i}'>{p}</label><!-- /HTTP_FORM_LABEL--><!--HTTP_FORM_PARAM--><br/><input id='{i}'name='{n}'length='{l}'placeholder='{p}'value='{v}' {c}><!-- /HTTP_FORM_PARAM--><!--HTTP_FORM_END--><br/><button type='submit'>Save</button></form><!-- /HTTP_FORM_END--><!--HTTP_SCAN_LINK--><br/><form action='/wifi'method='get'><button>Refresh</button></form><!-- /HTTP_SCAN_LINK--><!--HTTP_SAVED--><div class='msg'><h4>Saving Credentials</h4>Trying to connect ESP to network.<br/>If it fails reconnect to AP to try again</div><!-- /HTTP_SAVED--><!--HTTP_STATUS_ON--><div class='msg P'><strong>Connected</strong>to{v}<br/><em><small>with IP{i}</small></em></div><!-- /HTTP_STATUS_ON--><!--HTTP_STATUS_OFF--><div class='msg{c}'><strong>Not Connected</strong>to{v}{r}</div><!-- /HTTP_STATUS_OFF--><!--sample--><div class='msg D'><strong>Not Connected</strong>to apname<!-- /sample--><!--HTTP_STATUS_OFFPW--><br/>Authentication Failure<!-- /HTTP_STATUS_OFFPW--><!--HTTP_STATUS_OFFNOAP--><br/>AP not found<!-- /HTTP_STATUS_OFFNOAP--><!--HTTP_STATUS_OFFFAIL--><br/>Could not Connect<!-- /HTTP_STATUS_OFFFAIL--></div><!--HTTP_STATUS_NONE--><div class='msg'>No AP set</div><!-- /HTTP_STATUS_NONE--><!--SAMPLE--><div class='msg P'><h4>H4 Color Header</h4>content</div><!-- /SAMPLE--><!--SAMPLE--><h2>/info</h3><hr><dl><dt>Chip ID</dt><dd>123456</dd><dt>Flash Chip ID</dt><dd>1234556</dd><dt>IDE Flash Size</dt><dd>4194304 bytes</dd><dt>Real Flash Size</dt><dd>4194304 bytes</dd><dt>Empty</dt><dd></dd><dt>Soft AP IP</dt><dd>192.168.4.1</dd><dt>Soft AP MAC</dt><dd>00:00:00:00:00:00</dd><dt>Station MAC</dt><dd>00:00:00:00:00:00</dd></dl>";
const char SAMPLE[] PROGMEM               = "<h2>/</h2><hR><!-- /SAMPLE--><!--HTTP_PORTAL_OPTIONS--><!-- /HTTP_PORTAL_OPTIONS--><!--HTTP_PORTAL_MENU[] --><form action='/wifi'method='get'><button>Configure WiFi</button></form><br/><form action='/0wifi'method='get'><button>Configure WiFi(No Scan)</button></form><br/><form action='/info'method='get'><button>Info</button></form><br/><form action='/param'method='get'><button>Setup</button></form><br/><Hr><br/><form action='/close'method='post'><button>Close</button></form><br/><form action='/erase'method='post'><button class='D'>Erase</button></form><br/><form action='/restart'method='post'><button>Restart</button></form><br/><form action='/exit'method='post'><button>Exit</button></form><br/><!-- /HTTP_PORTAL_MENU--><!--SAMPLE--><h2>/wifi</h2><hr><div><a href='#p'onclick='c(this)'>Acccess Point 01</a><div role='img'aria-label='88%'title='88%'class='q q-4 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 02</a><div role='img'aria-label='88%'title='88%'class='q q-4'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 03</a><div role='img'aria-label='60%'title='60%'class='q q-3 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 04</a><div role='img'aria-label='60%'title='60%'class='q q-3'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 05</a><div role='img'aria-label='60%'title='60%'class='q q-3'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 06</a><div role='img'aria-label='40%'title='40%'class='q q-2'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 07</a><div role='img'aria-label='40%'title='40%'class='q q-2 l'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 08</a><div role='img'aria-label='20%'title='20%'class='q q-1'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 09</a><div role='img'aria-label='20%'title='20%'class='q q-1'></div></div><div><a href='#p'onclick='c(this)'>Acccess Point 10</a><div role='img'aria-label='20%'title='20%'class='q q-4 l'></div><div class='q'>100%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 11</a><div role='img'aria-label='10%'title='10%'class='q q-3'></div><div class='q'>70%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 12</a><div role='img'aria-label='10%'title='10%'class='q q-1 l'></div><div class='q'>10%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 13</a><div role='img'aria-label='10%'title='10%'class='q q-0 h'></div><div class='q'>100%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 14</a><div class='q'>66%</div></div><div><a href='#p'onclick='c(this)'>Acccess Point 15</a><div class='q'>56%</div></div><!-- /SAMPLE--><!--HTTP_ITEM--><div><a href='#p'onclick='c(this)'>{v}</a><div role='img'aria-label='{r}%'title='{r}%'class='q q-{q} {i}'></div></div><!-- /HTTP_ITEM--><!--HTTP_FORM_START--><form method='get'action='wifisave'><label for='s'>SSID</label><br/><input id='s'name='s'length=32 placeholder='SSID'><br/><label for='p'>Password</label><input id='p'name='p'length=64 type='password'placeholder='password'><br/><!-- /HTTP_FORM_START--><!--SAMPLE--><h3>custom parameter</h3><hr><br/><label for='custom'>Label for Custom Param</label><br/><input id='custom'name='custom'length='255'placeholder='placeholder'value='' {c}><!-- /SAMPLE--><!--HTTP_FORM_LABEL--><br/><label for='{i}'>{p}</label><!-- /HTTP_FORM_LABEL--><!--HTTP_FORM_PARAM--><br/><input id='{i}'name='{n}'length='{l}'placeholder='{p}'value='{v}' {c}><!-- /HTTP_FORM_PARAM--><!--HTTP_FORM_END--><br/><button type='submit'>Save</button></form><!-- /HTTP_FORM_END--><!--HTTP_SCAN_LINK--><br/><form action='/wifi'method='get'><button>Refresh</button></form><!-- /HTTP_SCAN_LINK--><!--HTTP_SAVED--><div class='msg'><h4>Saving Credentials</h4>Trying to connect ESP to network.<br/>If it fails reconnect to AP to try again</div><!-- /HTTP_SAVED--><!--HTTP_STATUS_ON--><div class='msg P'><strong>Connected</strong>to{v}<br/><em><small>with IP{i}</small></em></div><!-- /HTTP_STATUS_ON--><!--HTTP_STATUS_OFF--><div class='msg{c}'><strong>Not Connected</strong>to{v}{r}</div><!-- /HTTP_STATUS_OFF--><!--sample--><div class='msg D'><strong>Not Connected</strong>to apname<!-- /sample--><!--HTTP_STATUS_OFFPW--><br/>Authentication Failure<!-- /HTTP_STATUS_OFFPW--><!--HTTP_STATUS_OFFNOAP--><br/>AP not found<!-- /HTTP_STATUS_OFFNOAP--><!--HTTP_STATUS_OFFFAIL--><br/>Could not Connect<!-- /HTTP_STATUS_OFFFAIL--></div><!--HTTP_STATUS_NONE--><div class='msg'>No AP set</div><!-- /HTTP_STATUS_NONE--><!--SAMPLE--><div class='msg P'><h4>H4 Color Header</h4>content</div><!-- /SAMPLE--><!--SAMPLE--><h2>/info</h3><hr><dl><dt>Chip ID</dt><dd>123456</dd><dt>Flash Chip ID</dt><dd>1234556</dd><dt>IDE Flash Size</dt><dd>4194304 bytes</dd><dt>Real Flash Size</dt><dd>4194304 bytes</dd><dt>Empty</dt><dd></dd><dt>Soft AP IP</dt><dd>192.168.4.1</dd><dt>Soft AP MAC</dt><dd>00:00:00:00:00:00</dd><dt>Station MAC</dt><dd>00:00:00:00:00:00</dd></dl>";
const char HTTP_HELP[] PROGMEM            = "<br/><h3>Available Pages</h3><hr><table class='table'><thead><tr><th>Page</th><th>Function</th></tr></thead><tbody><tr><td><a href='/'>/</a></td><td>Menu page.</td></tr><tr><td><a href='/wifi'>/wifi</a></td><td>Show WiFi scan results and enter WiFi configuration.(/0wifi noscan)</td></tr><tr><td><a href='/wifisave'>/wifisave</a></td><td>Save WiFi configuration information and configure device.Needs variables supplied.</td></tr><tr><td><a href='/close'>/close</a></td><td>Close the configuration server and configuration WiFi network.</td></tr><tr><td><a href='/info'>/info</a></td><td>Information page</td></tr><tr><td><a href='/close'>/close</a></td><td>Close the captiveportal popup,configportal will remain active</td></tr><tr><td><a href='/exit'>/exit</a></td><td>Exit Config Portal,configportal will close</td></tr><tr><td><a href='/restart'>/restart</a></td><td>Reboot the device</td></tr><tr><td><a href='/erase'>/erase</a></td><td>Erase WiFi configuration and reboot Device.Device will not reconnect to a network until new WiFi configuration data is entered.</td></tr></table><p/>More information about WiFiManager at<a href='https://github.com/tzapu/WiFiManager'>https://github.com/tzapu/WiFiManager</a>";
const char FORM_UPLOAD[] PROGMEM          = "<Br/><br/>Form UPLOAD<br/><form method='POST'action='u'enctype='multipart/form-data'><input type='file'name='update'accept='.bin,application/octet-stream'><button type='submit'value='Submit'>Submit</button></form>";
const char HTTP_END[] PROGMEM             = "</div></body></html>";
