<?php
namespace {

	class SASS {

		const STYLE_NESTED = 0;
		const STYLE_EXPANDED  = 1;
		const STYLE_COMPACT = 2;
		const STYLE_COMPRESSED = 3;

		/**
		 * @static
		 * @param string $string
		 * @param int $options
		 * @return string
		 * @throws SASS\CompileErrorException
		 */
		public static function compile($string, $options = 0) {}

		/**
		 * @static
		 * @param string $input
		 * @param string $output
		 * @param int $options
		 * @return int
		 * @throws SASS\CompileErrorException
		 */
		public static function compileFile($input, $output, $options = 0) {}

		/**
		 * @static
		 * @param string $input
		 * @param string $output
		 * @param int $options
		 * @return int
		 * @throws SASS\CompileErrorException
		 */
		public static function compileFolder($input, $output, $options = 0) {}
	}

}

namespace SASS {

	class CompileErrorException extends \Exception {}
}
?>