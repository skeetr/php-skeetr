dnl $Id$
dnl config.m4 for extension skeetr

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(skeetr, for skeetr support,
dnl Make sure that the comment is aligned:
dnl [  --with-skeetr           Include skeetr support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(skeetr, whether to enable skeetr support,
[  --enable-skeetr         Enable skeetr support])

if test "$PHP_ECHO" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-skeetr -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/skeetr.h"  # you most likely want to change this
  dnl if test -r $PHP_ECHO/$SEARCH_FOR; then # path given as parameter
  dnl   ECHO_DIR=$PHP_ECHO
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for skeetr files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ECHO_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ECHO_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the skeetr distribution])
  dnl fi

  dnl # --with-skeetr -> add include path
  dnl PHP_ADD_INCLUDE($SKEETR_DIR/include)

  dnl # --with-skeetr -> check for lib and symbol presence
  dnl LIBNAME=skeetr # you may want to change this
  dnl LIBSYMBOL=skeetr # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SKEETR_DIR/lib, ECHO_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ECHOLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong skeetr lib version or lib not found])
  dnl ],[
  dnl   -L$SKEETR_DIR/lib -lm -ldl
  dnl ])
  dnl
  dnl PHP_SUBST(ECHO_SHARED_LIBADD)

  PHP_NEW_EXTENSION(skeetr, skeetr.c, $ext_shared)
fi
