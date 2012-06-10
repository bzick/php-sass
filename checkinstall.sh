phpize
./configure --with-sass
make -j2
checkinstall --install=yes --pkgname=php-sass --pkgversion=0.1 --maintainer=a.cobest@gmail.com --pkgrelease=20120610 -y --strip=yes --stripso=yes