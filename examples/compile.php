<?php

print_r(SASS::compile("div { a { color: black}}"));

//var_dump(SASS::compileFile(__DIR__."/styles/file21.inv.sass"));
var_dump(SASS::compileFolder(__DIR__."/styles/*", __DIR__."/styles2/"));

var_dump("exit");
?>