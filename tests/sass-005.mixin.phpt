--TEST--
Test simple CSS (without SASS)
--CREDITS--
Ivan Shalganov <a.cobest@gmail.com>
--FILE--
<?php
	echo SASS::compile(
'@mixin table-base {
  th {
    text-align: center;
    font-weight: bold;
  }
  td, th {padding: 2px}
}

@mixin left($dist) {
  float: left;
  margin-left: $dist;
}

#data {
  @include left(10px);
  @include table-base;
}',
  SASS::STYLE_NESTED);
?>
--EXPECT--
#data {
  float: left;
  margin-left: 10px; }
  #data th {
    text-align: center;
    font-weight: bold; }
  #data td, #data th {
    padding: 2px; }