static const char mainhtmPage[] = R"~(
<!DOCTYPE html>
<meta name="viewport" content="width=device-width, initial-scale=1">
<html>
<head>
<title>Quadruloop</title>
<link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<div class="header-fixed">Quadruloop: <span id="state">ready!</span></div>

<div class="content">

<button onclick="l('ST');">Stand</button>
<button onclick="l('WH');">Wheel</button>
<hr />

<button onclick="l(elv('txt'));">Send Command</button>
&nbsp;
<input type="text" id="txt" />
</div>

<script type="text/javascript">
    function el(id) { return document.getElementById(id); }
    function elv(id) { return el(id).value; }
    function l(cmd, p1, p2) {
        var xhReq = new XMLHttpRequest();
        var uri = '/cmd?action=' + cmd;
        if (p1) { uri += '&p1=' + encodeURIComponent(p1); }
        if (p2) { uri += '&p2=' + encodeURIComponent(p2); }
        xhReq.open('GET', uri, true);
  try {
          xhReq.send();
          xhReq.onload = function () {
            el('state').innerText = this.responseText;
          }
  } catch(ex) {
    el('state').innerText = 'send error';
  }
    };
</script>
</body>
</html>
)~";

static const char stylecssPage[] = R"~(
body, button,input {font-family:sans-serif; font-size: 22px;}
body {
    padding: 5% 5%;
}
a, button {
    display:inline-block;
    width:45%;
    background-color:#337ab7;
    text-align:center;
    border:1px solid #2e6da4;
    border-radius:4px;
    text-decoration:none;
    color:#fff;
    vertical-align:middle;
    padding: 12px 0;
}
a+a, button+button {
    margin-left:5%;
}
a:hover, button:hover {
    background-color:#23527c;
}
input {
    display:inline-block;
    width: 30%;
    margin-bottom:12px;
}
.header-fixed {
    width:100%;
    position:fixed;
    top:0px;
    left:0px;
    background-color:#337ab7;
    color:#fff;
    padding: 5px;
}
.content {
    padding-top: 15px;
    text-align: center;
}
.button30 {
    width: 28%;
}
)~";

