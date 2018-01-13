dnl $Id$
dnl config.m4 for extension s2go

dnl If your extension references something external, use with:

PHP_ARG_WITH(s2go, for s2go support,
[  --with-s2go[=DIR]             Include s2go support])

if test "$PHP_S2GO" != "no"; then
  PHP_NEW_EXTENSION(s2go, s2go.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
  PHP_SUBST(S2GO_SHARED_LIBADD)

  SEARCH_PATH="/usr/local /usr"     # you might want to change this
  SEARCH_FOR="/include/libs2go.h"  # you most likely want to change this
  if test -r $PHP_S2GO/$SEARCH_FOR; then # path given as parameter
    S2GO_DIR=$PHP_S2GO
  else # search default path list
    AC_MSG_CHECKING([for test files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        S2GO_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  PHP_ADD_LIBRARY_WITH_PATH(s2go, "${S2GO_DIR}/${PHP_LIBDIR}", S2GO_SHARED_LIBADD)
 fi
