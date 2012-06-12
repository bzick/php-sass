<?php
namespace {

    /**
     * SASS compiler via libsass
     * @author Ivan Shalganov <a.cobest@gmail.com>
     * @link https://github.com/hcatlin/libsass libsass
     * @link http://sass-lang.com/ SASS language
     * */
    class SASS {

        /**
         * Version of the extension
         * */
        const VERSION_NUMBER = 2; // mean 0.2
        
        /**
         * 'Nested' format
         * */
        const STYLE_NESTED = 0;
        
        /**
         * Not implemented in libsass
         * @link https://github.com/hcatlin/libsass/issues/15
         * */
        const STYLE_EXPANDED  = 1;
        
        /**
         * Not implemented in libsass
         * @link https://github.com/hcatlin/libsass/issues/15
         * */
        const STYLE_COMPACT = 2;
        
        /**
         * Not implemented in libsass
         * @link https://github.com/hcatlin/libsass/issues/15
         * */
        const STYLE_COMPRESSED = 3;

        /**
         * Compile string
         * @static
         * @param string $string input SASS string
         * @param int $options one of the constants SASS::STYLE_*
         * @param string $include_paths *not implemented*
         * @return string output CSS
         * @throws SASS\CompileErrorException if compilation failed
         */
        public static function compile($string, $options = self::STYLE_NESTED, $include_paths = null) {}

        /**
         * Compile file
         * @static
         * @param string $filename input filename
         * @param int $options one of the constants SASS::STYLE_*
         * @param string $include_paths *not implemented*
         * @return string compiled content of the file
         * @throws SASS\CompileErrorException if compilation failed or invalid arguments given
         */
        public static function compileFile($filename, $options = self::STYLE_NESTED, $include_paths = null) {}

        /**
         * Not implemented
         * Compile directory recursively
         * @static
         * @param string $input input directory
         * @param string $output output directory
         * @param int $options one of the constants SASS::STYLE_*
         * @param string $include_paths *not implemented*
         * @throws SASS\CompileErrorException if compilation failed or invalid arguments given
         */
        public static function compileFolder($input, $output, $options = self::STYLE_NESTED, $include_paths = null) {}
    }

}

namespace SASS {

    /**
     * Runtime compilation error
     * */
    class CompileErrorException extends \Exception {}
}
?>