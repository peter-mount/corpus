# Maintainer: Peter Mount <peter@retep.org>

pkgname="nrod-corpus"
pkgver="0.1"
pkgrel="2"
pkgdesc="Area51 Network Rail Corpus Database"
arch="x86_64"
url="https://area51.onl/"
license="ASL 2.0"
source=""
subpackages="$pkgname-dev"
depends="libarea51 libarea51-rest json-c libmicrohttpd"
depends_dev="libarea51-dev libarea51-rest-dev json-c-dev libmicrohttpd-dev"
#triggers="$pkgname-bin.trigger=/lib:/usr/lib:/usr/glibc-compat/lib"

builddeps() {
  sudo apk add $depends $depends_dev
}

package() {
  autoconf
  ./configure
  make clean
  make -j1
  mkdir -p "$pkgdir/usr/bin"
  cp -rp build/package/usr/bin/* "$pkgdir/usr/bin"
  mkdir -p "$pkgdir/usr/lib"
  cp -rp build/package/usr/lib/* "$pkgdir/usr/lib"
}

dev() {
  depends="$pkgname nrod-corpus"
  mkdir -p "$subpkgdir/usr/include"
  cp -rp build/package/usr/include/* "$subpkgdir/usr/include"
  rm -f "$subpkgdir/usr/include/networkrail/corpus/version.*"
}
