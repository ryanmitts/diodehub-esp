/**
 * strings_en.h
 * engligh strings for
 * WiFiManager, a library for the ESP8266/Arduino platform
 * for configuration of WiFi credentials using a Captive Portal
 * 
 * @author Creator tzapu
 * @author tablatronix
 * @version 0.0.0
 * @license MIT
 */

#ifndef WIFI_MANAGER_OVERRIDE_STRINGS
// !!! THIS DOES NOT WORK, you cannot define in a sketch, if anyone one knows how to order includes to be able to do this help!

const char HTTP_HEAD_START[]       PROGMEM = "<!DOCTYPE html><html lang='en'><head><meta name='format-detection' content='telephone=no'><meta charset='UTF-8'><meta  name='viewport' content='width=device-width,initial-scale=1,user-scalable=no'/><title>{v}</title>";
const char HTTP_SCRIPT[]           PROGMEM = "<script>function c(l){document.getElementById('s').value=l.innerText||l.textContent;document.getElementById('p').focus();}</script>";
const char HTTP_HEAD_END[] PROGMEM        = "</head><body><div class='header'><a class='logo-link'href='/'><img class='logo'src='/logo.svg'></a></div><div class='wrap'><!-- <div class='wrap ql qinv'> -->";

const char HTTP_ROOT_MAIN[]        PROGMEM = "<h1>{v}</h1><h3>DiodeHub Configuration</h3>";
const char * const HTTP_PORTAL_MENU[] PROGMEM = {
"<form action='/wifi'    method='get'><button>Configure (WiFi Scan)</button></form><br/>\n", // MENU_WIFI
"<form action='/0wifi'   method='get'><button>Configure (No WiFi Scan)</button></form><br/>\n", // MENU_WIFINOSCAN
"<form action='/info'    method='get'><button>Info</button></form><br/>\n", // MENU_INFO
"<form action='/param'   method='get'><button>Setup</button></form><br/>\n",//MENU_PARAM
"<form action='/close'   method='get'><button>Close</button></form><br/>\n", // MENU_CLOSE
"<form action='/restart' method='get'><button>Restart</button></form><br/>\n",// MENU_RESTART
"<form action='/exit'    method='get'><button>Exit</button></form><br/>\n",  // MENU_EXIT
"<form action='/erase'   method='get'><button class='D'>Erase</button></form><br/>\n", // MENU_ERASE
"<hr><br/>" // MENU_SEP
};

// const char HTTP_PORTAL_OPTIONS[]   PROGMEM = strcat(HTTP_PORTAL_MENU[0] , HTTP_PORTAL_MENU[3] , HTTP_PORTAL_MENU[7]);
const char HTTP_PORTAL_OPTIONS[]   PROGMEM = "";
const char HTTP_ITEM_QI[]          PROGMEM = "<div role='img' aria-label='{r}%' title='{r}%' class='q q-{q} {i} {h}'></div>"; // rssi icons
const char HTTP_ITEM_QP[]          PROGMEM = "<div class='q {h}'>{r}%</div>"; // rssi percentage
const char HTTP_ITEM[]             PROGMEM = "<div><a href='#p' onclick='c(this)'>{v}</a>{qi}{qp}</div>"; // {q} = HTTP_ITEM_QI, {r} = HTTP_ITEM_QP
// const char HTTP_ITEM[]            PROGMEM = "<div><a href='#p' onclick='c(this)'>{v}</a> {R} {r}% {q} {e}</div>"; // test all tokens

const char HTTP_FORM_START[]       PROGMEM = "<form method='POST' action='{v}'>";
const char HTTP_FORM_WIFI[]        PROGMEM = "<label for='s'>SSID</label><input id='s' name='s' maxlength='32' autocorrect='off' autocapitalize='none' placeholder='{v}'><br/><label for='p'>Password</label><input id='p' name='p' maxlength='64' type='password' placeholder=''>";
const char HTTP_FORM_WIFI_END[]    PROGMEM = "";
const char HTTP_FORM_STATIC_HEAD[] PROGMEM = "<hr><br/>";
const char HTTP_FORM_END[]         PROGMEM = "<br/><br/><button type='submit'>Save</button></form>";
const char HTTP_FORM_LABEL[]       PROGMEM = "<label for='{i}'>{t}</label>";
const char HTTP_FORM_PARAM_HEAD[]  PROGMEM = "<br/><hr><br/>";
const char HTTP_FORM_PARAM[]       PROGMEM = "<br/><input id='{i}' name='{n}' maxlength='{l}' value='{v}' {c}>";

const char HTTP_SCAN_LINK[]        PROGMEM = "<br/><form action='/wifi?refresh=1' method='POST'><button name='refresh' value='1'>Refresh</button></form>";
const char HTTP_SAVED[]            PROGMEM = "<div class='msg'>Saving Credentials<br/>Trying to connect ESP to network.<br />If it fails reconnect to AP to try again</div>";
const char HTTP_PARAMSAVED[]       PROGMEM = "<div class='msg'>Saved<br/></div>";
const char HTTP_END[]              PROGMEM = "</div></body></html>";
const char HTTP_ERASEBTN[]         PROGMEM = "<br/><form action='/erase' method='get'><button class='D'>Erase WiFi Config</button></form>";

const char HTTP_STATUS_ON[]        PROGMEM = "<div class='msg P'><strong>Connected</strong> to {v}<br/><em><small>with IP {i}</small></em></div>";
const char HTTP_STATUS_OFF[]       PROGMEM = "<div class='msg {c}'><strong>Not Connected</strong> to {v}{r}</div>";
const char HTTP_STATUS_OFFPW[]     PROGMEM = "<br/>Authentication Failure"; // STATION_WRONG_PASSWORD,  no eps32
const char HTTP_STATUS_OFFNOAP[]   PROGMEM = "<br/>AP not found";   // WL_NO_SSID_AVAIL
const char HTTP_STATUS_OFFFAIL[]   PROGMEM = "<br/>Could not Connect"; // WL_CONNECT_FAILED
const char HTTP_STATUS_NONE[]      PROGMEM = "<div class='msg'>No AP set</div>";
const char HTTP_BR[]               PROGMEM = "<br/>";

const char HTTP_STYLE[] PROGMEM           = "<style> :root{ /*CSS VARIABLE THEME COLOR*/ /*--primarycolor:#9933CC;*/ --primarycolor:#558EF8; }body.invert,body.invert a,body.invert h1{ background-color:#060606;color:white; }body.invert.msg{background-color: #282828;border-top:1px solid#555;border-right:1px solid#555;border-bottom:1px solid#555;color:#fff; }body.invert.q[role=img] { -webkit-filter:invert(1);filter:invert(1); } .c,body{ text-align:center;font-family:verdana;margin:0; } .wrap{ text-align:left;display:inline-block;min-width:260px;max-width:500px; }div,input{ padding:5px;font-size:1em; /*width:100%;*/margin:5px 0;box-sizing:border-box; }input,button,.msg{width:100%; }button,input[type=\"button\"],input[type=\"submit\"] {border:0;background-color:var(--primarycolor);color: #fff;line-height:2.4rem;font-size:1.2rem;cursor:pointer;outline:none; }button:hover,input[type=\"button\"]:hover,input[type=\"submit\"]:hover{ filter:brightness(0.9); }input[type=\"file\"]{border:1px solid var(--primarycolor); }a {color: #000;font-weight:700;text-decoration:none; }a:hover{ color:var(--primarycolor);text-decoration:underline; } .h{ display:none; } .q{ height:16px;margin:0;padding:0 5px;text-align:right;min-width:38px;float:right; } .q.q-0:after{ background-position-x:0; } .q.q-1:after{ background-position-x: -16px; } .q.q-2:after{ background-position-x: -32px; } .q.q-3:after{ background-position-x: -48px; } .q.q-4:after{ background-position-x: -64px; } .q.l:before{ background-position-x: -80px;padding-right:5px} .ql.q{ float:left; } .q:after, .q:before{ content: '';width:16px;height:16px;display:inline-block;background-repeat:no-repeat;background-position:16px 0;background-image:url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAAAQCAMAAADeZIrLAAAAJFBMVEX///8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADHJj5lAAAAC3RSTlMAIjN3iJmqu8zd7vF8pzcAAABsSURBVHja7Y1BCsAwCASNSVo3/v+/BUEiXnIoXkoX5jAQMxTHzK9cVSnvDxwD8bFx8PhZ9q8FmghXBhqA1faxk92PsxvRc2CCCFdhQCbRkLoAQ3q/wWUBqG35ZxtVzW4Ed6LngPyBU2CobdIDQ5oPWI5nCUwAAAAASUVORK5CYII='); } @media(-webkit-min-device-pixel-ratio:2), (min-resolution:192dpi) { .q:before, .q:after{ background-image:url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAALwAAAAgCAMAAACfM+KhAAAALVBMVEX///8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAADAOrOgAAAADnRSTlMAESIzRGZ3iJmqu8zd7gKjCLQAAACmSURBVHgB7dDBCoMwEEXRmKlVY3L//3NLhyzqIqSUggy8uxnhCR5Mo8xLt+14aZ7wwgsvvPA/ofv9+44334UXXngvb6XsFhO/VoC2RsSv9J7x8BnYLW+AjT56ud/uePMdb7IP8Bsc/e7h8Cfk912ghsNXWPpDC4hvN+D1560A1QPORyh84VKLjjdvfPFm++i9EWq0348XXnjhhT+4dIbCW+WjZim9AKk4UZMnnCEuAAAAAElFTkSuQmCC');background-size:95px 16px; } } .msg{ padding:20px;margin:20px 0;border:1px solid#eee;border-left-width:5px;border-left-color: #777; } .msg h4{ margin-top:0;margin-bottom:5px; } .msg.P{ border-left-color:var(--primarycolor); } .msg.P h4{ color:var(--primarycolor); } /*.msg.S{ border-left-color: #5cb85c; } .msg.S h4{ color: #5cb85c; }*/ .msg.D{ border-left-color: #dc3630; } .msg.D h4{ color: #dc3630; }dt{ font-weight:bold; }dd{ margin:0;padding:0 0 0.5em 0; }td{ vertical-align:top; }button.D{background-color:#dc3630; } .header{ width:100%;background-color: #24252a;padding:8px;margin:0;height:64px;display:flex;align-items:middle;box-shadow:0px 2px 4px-1px rgba(0,0,0,0.2),0px 4px 5px 0px rgba(0,0,0,0.14),0px 1px 10px 0px rgba(0,0,0,0.12); } .logo-link{ display:flex; } .logo{ width:10rem;margin-left:8px; } </style>";

const char HTTP_HELP[]             PROGMEM =
 "<br/><h3>Available Pages</h3><hr>"
 "<table class='table'>"
 "<thead><tr><th>Page</th><th>Function</th></tr></thead><tbody>"
 "<tr><td><a href='/'>/</a></td>"
 "<td>Menu page.</td></tr>"
 "<tr><td><a href='/wifi'>/wifi</a></td>"
 "<td>Show WiFi scan results and enter WiFi configuration.(/0wifi noscan)</td></tr>"
 "<tr><td><a href='/wifisave'>/wifisave</a></td>"
 "<td>Save WiFi configuration information and configure device. Needs variables supplied.</td></tr>"
 "<tr><td><a href='/param'>/param</a></td>"
 "<td>Parameter page</td></tr>"
 "<tr><td><a href='/info'>/info</a></td>"
 "<td>Information page</td></tr>"
 "<tr><td><a href='/close'>/close</a></td>"
 "<td>Close the captiveportal popup,configportal will remain active</td></tr>"
 "<tr><td><a href='/exit'>/exit</a></td>"
 "<td>Exit Config Portal, configportal will close</td></tr>"
 "<tr><td><a href='/restart'>/restart</a></td>"
 "<td>Reboot the device</td></tr>"
 "<tr><td><a href='/erase'>/erase</a></td>"
 "<td>Erase WiFi configuration and reboot Device. Device will not reconnect to a network until new WiFi configuration data is entered.</td></tr>"
 "</table>"
 "<p/>More information about WiFiManager at <a href='https://github.com/tzapu/WiFiManager'>https://github.com/tzapu/WiFiManager</a>.";

#ifdef JSTEST
const char HTTP_JS[] PROGMEM = 
"<script>function postAjax(url, data, success) {"
"    var params = typeof data == 'string' ? data : Object.keys(data).map("
"            function(k){ return encodeURIComponent(k) + '=' + encodeURIComponent(data[k]) }"
"        ).join('&');"
"    var xhr = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject(\"Microsoft.XMLHTTP\");"
"    xhr.open('POST', url);"
"    xhr.onreadystatechange = function() {"
"        if (xhr.readyState>3 && xhr.status==200) { success(xhr.responseText); }"
"    };"
"    xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');"
"    xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');"
"    xhr.send(params);"
"    return xhr;}"
"postAjax('/status', 'p1=1&p2=Hello+World', function(data){ console.log(data); });"
"postAjax('/status', { p1: 1, p2: 'Hello World' }, function(data){ console.log(data); });"
"</script>";
#endif

// Info html
#ifdef ESP32
	const char HTTP_INFO_esphead[]    PROGMEM = "<h3>ESP32</h3><hr><dl>";
	const char HTTP_INFO_chiprev[]    PROGMEM = "<dt>Chip Rev</dt><dd>{1}</dd>";
  const char HTTP_INFO_lastreset[]    PROGMEM = "<dt>Last reset reason</dt><dd>CPU0: {1}<br/>CPU1: {2}</dd>";
  const char HTTP_INFO_aphost[]       PROGMEM = "<dt>Acccess Point Hostname</dt><dd>{1}</dd>";  
#else 
	const char HTTP_INFO_esphead[]    PROGMEM = "<h3>esp8266</h3><hr><dl>";
	const char HTTP_INFO_flashsize[]  PROGMEM = "<dt>Real Flash Size</dt><dd>{1} bytes</dd>";
	const char HTTP_INFO_fchipid[]    PROGMEM = "<dt>Flash Chip ID</dt><dd>{1}</dd>";
	const char HTTP_INFO_corever[]    PROGMEM = "<dt>Core Version</dt><dd>{1}</dd>";
	const char HTTP_INFO_bootver[]    PROGMEM = "<dt>Boot Version</dt><dd>{1}</dd>";
	const char HTTP_INFO_memsketch[]  PROGMEM = "<dt>Memory - Sketch Size</dt><dd>Used / Total bytes<br/>{1} / {2}";
	const char HTTP_INFO_memsmeter[]  PROGMEM = "<br/><progress value='{1}' max='{2}'></progress></dd>";
	const char HTTP_INFO_lastreset[]  PROGMEM = "<dt>Last reset reason</dt><dd>{1}</dd>";
#endif

const char HTTP_INFO_freeheap[]   PROGMEM = "<dt>Memory - Free Heap</dt><dd>{1} bytes available</dd>"; 
const char HTTP_INFO_wifihead[]   PROGMEM = "<br/><h3>WiFi</h3><hr>";
const char HTTP_INFO_uptime[]     PROGMEM = "<dt>Uptime</dt><dd>{1} Mins {2} Secs</dd>";
const char HTTP_INFO_chipid[]     PROGMEM = "<dt>Chip ID</dt><dd>{1}</dd>";
const char HTTP_INFO_idesize[]    PROGMEM = "<dt>Flash Size</dt><dd>{1} bytes</dd>";
const char HTTP_INFO_sdkver[]     PROGMEM = "<dt>SDK Version</dt><dd>{1}</dd>";
const char HTTP_INFO_cpufreq[]    PROGMEM = "<dt>CPU Frequency</dt><dd>{1}MHz</dd>";
const char HTTP_INFO_apip[]       PROGMEM = "<dt>Access Point IP</dt><dd>{1}</dd>";
const char HTTP_INFO_apmac[]      PROGMEM = "<dt>Access Point MAC</dt><dd>{1}</dd>";
const char HTTP_INFO_apssid[]     PROGMEM = "<dt>SSID</dt><dd>{1}</dd>";
const char HTTP_INFO_apbssid[]    PROGMEM = "<dt>BSSID</dt><dd>{1}</dd>";
const char HTTP_INFO_staip[]      PROGMEM = "<dt>Station IP</dt><dd>{1}</dd>";
const char HTTP_INFO_stagw[]      PROGMEM = "<dt>Station Gateway</dt><dd>{1}</dd>";
const char HTTP_INFO_stasub[]     PROGMEM = "<dt>Station Subnet</dt><dd>{1}</dd>";
const char HTTP_INFO_dnss[]       PROGMEM = "<dt>DNS Server</dt><dd>{1}</dd>";
const char HTTP_INFO_host[]       PROGMEM = "<dt>Hostname</dt><dd>{1}</dd>";
const char HTTP_INFO_stamac[]     PROGMEM = "<dt>Station MAC</dt><dd>{1}</dd>";
const char HTTP_INFO_conx[]       PROGMEM = "<dt>Connected</dt><dd>{1}</dd>";
const char HTTP_INFO_autoconx[]   PROGMEM = "<dt>Autoconnect</dt><dd>{1}</dd>";
const char HTTP_INFO_temp[]       PROGMEM = "<dt>Temperature</dt><dd>{1} C&deg; / {2} F&deg;</dd>";

const char HTTP_INFO_diodehubhead[] PROGMEM = "<br/><h3>DiodeHub</h3><hr>";
const char HTTP_INFO_diodehubversion[] PROGMEM = "<dt>Version</dt><dd>{1}</dd>";
const char HTTP_INFO_diodehubmd5[] PROGMEM = "<dt>MD5</dt><dd>{1}</dd>";

// Strings
const char S_y[]                  PROGMEM = "Yes";
const char S_n[]                  PROGMEM = "No";
const char S_enable[]             PROGMEM = "Enabled";
const char S_disable[]            PROGMEM = "Disabled";
const char S_GET[]                PROGMEM = "GET";
const char S_POST[]               PROGMEM = "POST";
const char S_NA[]                 PROGMEM = "Unknown";

const char S_titlewifisaved[]     PROGMEM = "Credentials Saved";
const char S_titlewifi[]          PROGMEM = "DiodeHub - Device Config";
const char S_titleinfo[]          PROGMEM = "DiodeHub - Device Info";
const char S_titleparam[]         PROGMEM = "Setup";
const char S_titleparamsaved[]    PROGMEM = "Setup Saved";
const char S_titleexit[]          PROGMEM = "Exit";
const char S_titlereset[]         PROGMEM = "Reset";
const char S_titleerase[]         PROGMEM = "Erase";
const char S_titleclose[]         PROGMEM = "Close";
const char S_options[]            PROGMEM = "DiodeHub - Device Portal";
const char S_nonetworks[]         PROGMEM = "No networks found. Refresh to scan again.";
const char S_staticip[]           PROGMEM = "Static IP";
const char S_staticgw[]           PROGMEM = "Static Gateway";
const char S_staticdns[]          PROGMEM = "Static DNS";
const char S_subnet[]             PROGMEM = "Subnet";
const char S_exiting[]            PROGMEM = "Exiting";
const char S_resetting[]          PROGMEM = "Module will reset in a few seconds.";
const char S_closing[]            PROGMEM = "You can close the page, portal will continue to run";
const char S_error[]              PROGMEM = "An Error Occured";
const char S_notfound[]           PROGMEM = "File Not Found\n\n";
const char S_uri[]                PROGMEM = "URI: ";
const char S_method[]             PROGMEM = "\nMethod: ";
const char S_args[]               PROGMEM = "\nArguments: ";
const char S_parampre[]           PROGMEM = "param_";

// debug strings
const char D_HR[]                 PROGMEM = "--------------------";

// END WIFI_MANAGER_OVERRIDE_STRINGS
#endif

// -----------------------------------------------------------------------------------------------
// DO NOT EDIT BELOW THIS LINE

const uint8_t _nummenutokens = 9;
const char * const _menutokens[9] PROGMEM = {
    "wifi",
    "wifinoscan",
    "info",
    "param",
    "close",
    "restart",
    "exit",
    "erase",
    "sep"
};

const char R_root[]               PROGMEM = "/";
const char R_wifi[]               PROGMEM = "/wifi";
const char R_wifinoscan[]         PROGMEM = "/0wifi";
const char R_wifisave[]           PROGMEM = "/wifisave";
const char R_info[]               PROGMEM = "/info";
const char R_param[]              PROGMEM = "/param";
const char R_paramsave[]          PROGMEM = "/paramsave";
const char R_restart[]            PROGMEM = "/restart";
const char R_exit[]               PROGMEM = "/exit";
const char R_close[]              PROGMEM = "/close";
const char R_erase[]              PROGMEM = "/erase"; 
const char R_status[]             PROGMEM = "/status";
const char R_diodehublogo[]       PROGMEM = "/logo.svg";


//Strings
const char S_ip[]                 PROGMEM = "ip";
const char S_gw[]                 PROGMEM = "gw";
const char S_sn[]                 PROGMEM = "sn";
const char S_dns[]                PROGMEM = "dns";

// softap ssid default prefix
#ifdef ESP8266
	const char S_ssidpre[]        PROGMEM = "ESP";
#elif defined(ESP32)
	const char S_ssidpre[]        PROGMEM = "ESP32";
#else
	const char S_ssidpre[]        PROGMEM = "WM";
#endif

//Tokens
//@todo consolidate and reduce
const char T_ss[]                 PROGMEM = "{"; // token start sentinel
const char T_es[]                 PROGMEM = "}"; // token end sentinel
const char T_1[]                  PROGMEM = "{1}"; // @token 1
const char T_2[]                  PROGMEM = "{2}"; // @token 2
const char T_v[]                  PROGMEM = "{v}"; // @token v
const char T_I[]                  PROGMEM = "{I}"; // @token I
const char T_i[]                  PROGMEM = "{i}"; // @token i
const char T_n[]                  PROGMEM = "{n}"; // @token n
const char T_p[]                  PROGMEM = "{p}"; // @token p
const char T_t[]                  PROGMEM = "{t}"; // @token t
const char T_l[]                  PROGMEM = "{l}"; // @token l
const char T_c[]                  PROGMEM = "{c}"; // @token c
const char T_e[]                  PROGMEM = "{e}"; // @token e
const char T_q[]                  PROGMEM = "{q}"; // @token q
const char T_r[]                  PROGMEM = "{r}"; // @token r
const char T_R[]                  PROGMEM = "{R}"; // @token R
const char T_h[]                  PROGMEM = "{h}"; // @token h

// http
const char HTTP_HEAD_CL[]         PROGMEM = "Content-Length";
const char HTTP_HEAD_CT[]         PROGMEM = "text/html";
const char HTTP_HEAD_CT2[]        PROGMEM = "text/plain";
const char HTTP_HEAD_CT_SVG[]     PROGMEM = "image/svg+xml";
const char HTTP_HEAD_CORS[]       PROGMEM = "Access-Control-Allow-Origin";
const char HTTP_HEAD_CORS_ALLOW_ALL[]  PROGMEM = "*";

const char * const WIFI_STA_STATUS[] PROGMEM
{
  "WL_IDLE_STATUS",     // 0 STATION_IDLE
  "WL_NO_SSID_AVAIL",   // 1 STATION_NO_AP_FOUND
  "WL_SCAN_COMPLETED",  // 2
  "WL_CONNECTED",       // 3 STATION_GOT_IP
  "WL_CONNECT_FAILED",  // 4 STATION_CONNECT_FAIL, STATION_WRONG_PASSWORD(NI)
  "WL_CONNECTION_LOST", // 5
  "WL_DISCONNECTED",    // 6 
  "WL_STATION_WRONG_PASSWORD" // 7 KLUDGE 
};

#ifdef ESP32
const char * const AUTH_MODE_NAMES[] PROGMEM
{
    "OPEN",
    "WEP",             
    "WPA_PSK",         
    "WPA2_PSK",        
    "WPA_WPA2_PSK",    
    "WPA2_ENTERPRISE", 
    "MAX"
};
#elif defined(ESP8266)
const char * const AUTH_MODE_NAMES[] PROGMEM
{
    "",
    "",
    "WPA_PSK",      // 2 ENC_TYPE_TKIP
    "",
    "WPA2_PSK",     // 4 ENC_TYPE_CCMP
    "WEP",          // 5 ENC_TYPE_WEP
    "",
    "OPEN",         //7 ENC_TYPE_NONE
    "WPA_WPA2_PSK", // 8 ENC_TYPE_AUTO
};
#endif

const char* const WIFI_MODES[] PROGMEM = { "NULL", "STA", "AP", "STA+AP" };

#ifdef ESP32
const wifi_country_t WM_COUNTRY_US{"US",1,11,WIFI_COUNTRY_POLICY_AUTO};
const wifi_country_t WM_COUNTRY_CN{"CN",1,13,WIFI_COUNTRY_POLICY_AUTO};
const wifi_country_t WM_COUNTRY_JP{"JP",1,14,WIFI_COUNTRY_POLICY_AUTO};
#endif

const char HTTP_FAVICON[] PROGMEM = "<link rel=\"shortcut icon\" type=\"image/x-icon\" href=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAQAAADZc7J/AAAABGdBTUEAALGPC/xhBQAAACBjSFJNAAB6JgAAgIQAAPoAAACA6AAAdTAAAOpgAAA6mAAAF3CculE8AAAAAmJLR0QA/4ePzL8AAAAHdElNRQfjAg8IMRMyV5duAAADMElEQVRIx51UWUhUURj+zrl37p25szU6igumxVRoNU1W1LRZlJKthlK0UUFUkEQQPUQPPVQvvkTbgxFFC0Tri0EpkTgtpFFmJTVlK6TMENlozui9c+f0UDPNctP0v9yH83//951/4xAk2QoU8PfGd5cGF4adao4iMghh6udfSx5L/ZS2Z/3PYcI/bS12c85Z9lrxEw2DJX5UFXzWqwXllfrZYFrkV9ChLDenRvSTGInvldqMLYKPRKIeXW/GpRkTgVPJ9I0AXNNtHhoLJczcPLp8QfpKS6Er8yKn/PWb3hRVNJGqePouANluQzuJS9nwttgp4TqAOaiw2C7HY6I/Y91zUhqle2CBa5r0Kr5iwrKPAHsAAAx25JfwPfG44J9QCdT8FpiJxVm2e4ktI2r6Gi6WoR32XNqRGGHqmDE1DwzYAEZyD9OknkPmltP4KrPgTbqCpV9fbVwIjEXxdENnytBk63LjoAJgulDhOoC+J12b+rOTp0IgQcDgpui7tlRa+DmOQHnqYhBI2uuSYMFZ3nm8r0QuSIUoTFCHFFAs35bRH/NUXSrEIrISHlKAITifl51aqSqKt2dIPgDZQdUcLYBjJibFFcSBaAoMiDQsaQHW+uJPRbGTA65A5k2qURMDhN7k+YIRZqlODByF9BIumBoJxnPB1BeCQVlvdBpvmwZ8qxnJbo689G+W8yIai0HAc13ITAVCbuIm3/i+4DaGkDnSH9oR0WyCMECFl9rtYX/+vyctEz9QQxNV/mdgWkagv08zPMLnkQroeq23aGuHuZ6MUEB64npA8yNp50XfiO6XR5291k0X4dbTtAt02HQCa4O7bin4c2iLOI71uQNzh5n+57xDd3saQYGDaP6av8/8fjh0/Y+s/a0tWzEJFFiFWrx47Kg2ffx/esGB41erUQOAAsAWnEbrnTEbzY+H7gWB9CFv55Hau+pJICoAbMdptD8qWms/IXQPRudDthvjqt5daVaPRj1RaDsA25fCvY3XeraFyuRMFkvm+zTVDkKYLmB4ZDrjaujsY3GvQ8oOVSBXfDjZv6S/TKyjYuchBh66gOjVe9JuT2qp++nF6IT4X3fHcLfg/5KLAAAAJXRFWHRkYXRlOmNyZWF0ZQAyMDE5LTAyLTE1VDA4OjQ5OjE5KzAxOjAwqhikpgAAACV0RVh0ZGF0ZTptb2RpZnkAMjAxOS0wMi0xNVQwODo0OToxOSswMTowMNtFHBoAAAAZdEVYdFNvZnR3YXJlAEFkb2JlIEltYWdlUmVhZHlxyWU8AAAAV3pUWHRSYXcgcHJvZmlsZSB0eXBlIGlwdGMAAHic4/IMCHFWKCjKT8vMSeVSAAMjCy5jCxMjE0uTFAMTIESANMNkAyOzVCDL2NTIxMzEHMQHy4BIoEouAOoXEXTyQjWVAAAAAElFTkSuQmCC\">";
const char HTTP_DIODEHUB_LOGO[] PROGMEM = "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 831.39 200\"><title>new</title><path d=\"M100,0A100,100,0,0,0,83.71,198.67v-89.9H71.56a1.19,1.19,0,0,1-1.2-1.19V97.21a1.2,1.2,0,0,1,1.2-1.2h3.52L76,39a.61.61,0,0,1,0-.14A24.55,24.55,0,0,1,99.11,17.17c12.54-.67,24,8.74,25.7,21.68a1.28,1.28,0,0,1,0,.19V96h3.62a1.2,1.2,0,0,1,1.2,1.2v10.37a1.19,1.19,0,0,1-1.2,1.19H116.2V190h-6.75V108.77h-19v90.77c3.14.3,6.32.46,9.54.46A100,100,0,0,0,100,0Z\" style=\"fill:#fff\"/><path d=\"M274.58,136.72H240.21a3.14,3.14,0,0,1-3.67-3.67V67a3.14,3.14,0,0,1,3.67-3.67h34.37q12.75,0,18.92,5.1t6.18,15.71v31.82q0,10.61-6.18,15.71T274.58,136.72Zm-14.89-54v34.68h12.14a4.83,4.83,0,0,0,3.62-1.22,5.32,5.32,0,0,0,1.17-3.78V87.66a5.13,5.13,0,0,0-1.17-3.73,4.94,4.94,0,0,0-3.62-1.17Z\" style=\"fill:#fff\"/><path d=\"M314.67,136.72a3.86,3.86,0,0,1-2.81-.87,3.82,3.82,0,0,1-.86-2.8V120.91a3.86,3.86,0,0,1,.86-2.81,3.9,3.9,0,0,1,2.81-.86h10.1V83h-10.1A3.14,3.14,0,0,1,311,79.29V67a3.14,3.14,0,0,1,3.67-3.67h43.45A3.14,3.14,0,0,1,361.79,67V79.29A3.14,3.14,0,0,1,358.12,83h-9.89v34.27h9.89a3.13,3.13,0,0,1,3.67,3.67v12.14a3.14,3.14,0,0,1-3.67,3.67Z\" style=\"fill:#fff\"/><path d=\"M436.56,117.44a25,25,0,0,1-1.38,8.52,14.23,14.23,0,0,1-4.9,6.53,26.16,26.16,0,0,1-9.69,4.23,66.56,66.56,0,0,1-15.65,1.53,67.29,67.29,0,0,1-15.71-1.53,26.2,26.2,0,0,1-9.74-4.23,14.23,14.23,0,0,1-4.9-6.53,25,25,0,0,1-1.37-8.52V82.66a25,25,0,0,1,1.37-8.52,14.57,14.57,0,0,1,4.9-6.58,25.72,25.72,0,0,1,9.74-4.28,67.29,67.29,0,0,1,15.71-1.53,66.56,66.56,0,0,1,15.65,1.53,25.68,25.68,0,0,1,9.69,4.28,14.57,14.57,0,0,1,4.9,6.58,25,25,0,0,1,1.38,8.52Zm-40.19-3.67a4.42,4.42,0,0,0,1.53,3.42q1.53,1.36,7,1.37c3.67,0,6-.46,7-1.37a4.4,4.4,0,0,0,1.54-3.42V86.33A4.26,4.26,0,0,0,412,83c-1-.92-3.36-1.38-7-1.38s-6,.46-7,1.38a4.29,4.29,0,0,0-1.53,3.31Z\" style=\"fill:#fff\"/><path d=\"M487.56,136.72H453.18a3.15,3.15,0,0,1-3.67-3.67V67a3.15,3.15,0,0,1,3.67-3.67h34.38q12.75,0,18.92,5.1t6.17,15.71v31.82q0,10.61-6.17,15.71T487.56,136.72Zm-14.89-54v34.68H484.8a4.83,4.83,0,0,0,3.62-1.22,5.27,5.27,0,0,0,1.18-3.78V87.66a5.09,5.09,0,0,0-1.18-3.73,4.94,4.94,0,0,0-3.62-1.17Z\" style=\"fill:#fff\"/><path d=\"M576.6,136.72H529.27a3.15,3.15,0,0,1-3.67-3.67V67a3.15,3.15,0,0,1,3.67-3.67H576.6A3.14,3.14,0,0,1,580.27,67V78.89a3.14,3.14,0,0,1-3.67,3.67H548.45v7.85h19.89A3.15,3.15,0,0,1,572,94.08V105a3.15,3.15,0,0,1-3.67,3.67H548.45v8.77H576.6a3.14,3.14,0,0,1,3.67,3.67v11.94a3.14,3.14,0,0,1-3.67,3.67Z\" style=\"fill:#fff\"/><path d=\"M634.74,136.72H618.93a3.15,3.15,0,0,1-3.67-3.67V67a3.15,3.15,0,0,1,3.67-3.67h15.81A3.14,3.14,0,0,1,638.41,67V89.09h17V67a3.14,3.14,0,0,1,3.67-3.67h15.81A3.15,3.15,0,0,1,678.6,67v66.1a3.15,3.15,0,0,1-3.67,3.67H659.12a3.86,3.86,0,0,1-2.81-.87,3.82,3.82,0,0,1-.86-2.8V110.4h-17v22.65a3.14,3.14,0,0,1-3.67,3.67Z\" style=\"fill:#fff\"/><path d=\"M755.2,117.44a25,25,0,0,1-1.38,8.52,14.21,14.21,0,0,1-4.89,6.53,26.26,26.26,0,0,1-9.64,4.23,80.35,80.35,0,0,1-31.21,0,26.19,26.19,0,0,1-9.64-4.23,14.23,14.23,0,0,1-4.9-6.53,25,25,0,0,1-1.38-8.52V67a3.15,3.15,0,0,1,3.68-3.67h16A3.14,3.14,0,0,1,715.52,67v46.51a4.41,4.41,0,0,0,1.53,3.42q1.53,1.38,6.84,1.38t6.93-1.38a4.41,4.41,0,0,0,1.53-3.42V67A3.15,3.15,0,0,1,736,63.28h15.51A3.15,3.15,0,0,1,755.2,67Z\" style=\"fill:#fff\"/><path d=\"M811.61,136.72H772.44a3.14,3.14,0,0,1-3.67-3.67V67a3.14,3.14,0,0,1,3.67-3.67H805q10,0,14.79,3.82t4.79,11.79v4.89a14.44,14.44,0,0,1-1.48,7,9.12,9.12,0,0,1-4.54,4q6.53.61,9.69,4.49t3.16,11.32V120q0,8.57-4.84,12.65T811.61,136.72Zm-19.89-56.1v11h8.67a3.81,3.81,0,0,0,2.9-1,4.27,4.27,0,0,0,1-3.06V84.7a4.27,4.27,0,0,0-1-3.06,3.81,3.81,0,0,0-2.9-1Zm0,26.72v12H805a3.81,3.81,0,0,0,2.9-1,4.27,4.27,0,0,0,1-3.06v-4a4.1,4.1,0,0,0-1-3,4,4,0,0,0-2.9-1Z\" style=\"fill:#fff\"/></svg>";