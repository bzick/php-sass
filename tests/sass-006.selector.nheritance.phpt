--TEST--
Test simple CSS (without SASS)
--CREDITS--
Ivan Shalganov <a.cobest@gmail.com>
--FILE--
<?php
	echo SASS::compile(
'.error {
  border: 1px #f00;
  background: #fdd;
}
.error.intrusion {
  font-size: 1.3em;
  font-weight: bold;
}

.badError {
  @extend .error;
  border-width: 3px;
}',
  SASS::STYLE_NESTED);
?>
--EXPECT--
.error, .badError {
  border: 1px #f00;
  background: #fdd; }

.error.intrusion {
  font-size: 1.3em;
  font-weight: bold; }

.badError {
  border-width: 3px; }