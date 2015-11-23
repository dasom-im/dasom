dnl Process this file with autoconf to produce a configure script.

AC_INIT(dasom, 1.1, https://github.com/dasom-im/dasom/issues)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror])
AM_MAINTAINER_MODE([disable])
AM_SILENT_RULES([yes])

AM_PROG_AR
AC_PROG_CC

dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************

IT_PROG_INTLTOOL(0.35.0)
GETTEXT_PACKAGE=dasom
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [gettext package name])
AC_SUBST(GETTEXT_PACKAGE)
AM_GLIB_GNU_GETTEXT
AM_GLIB_DEFINE_LOCALEDIR(DASOM_LOCALE_DIR)

LT_INIT([disable-static])

LIBDASOM_REQUIRES="glib-2.0 gio-2.0 gio-unix-2.0 gmodule-2.0 gobject-introspection-1.0 x11"
LIBDASOM_PRIVATE="gtk+-3.0"
AC_SUBST(LIBDASOM_REQUIRES)
AC_SUBST(LIBDASOM_PRIVATE)

PKG_CHECK_MODULES(LIBDASOM_DEPS, [$LIBDASOM_REQUIRES $LIBDASOM_PRIVATE])
PKG_CHECK_MODULES(GLIB, [glib-2.0])
PKG_CHECK_MODULES(GIO, [gio-2.0])
PKG_CHECK_MODULES(GOBJECT, [gobject-2.0])
PKG_CHECK_MODULES(GTK3, [gtk+-3.0])
PKG_CHECK_MODULES(X11, [x11])

dnl ***************************************************************************
dnl  icon cache
dnl ***************************************************************************

AC_PATH_PROGS([GTK_UPDATE_ICON_CACHE],
              [gtk-update-icon-cache-3.0 gtk-update-icon-cache], [no],
              [/usr/bin:$GTK3_LIBDIR/libgtk-3-0:$GTK2_LIBDIR/libgtk2.0-0])
if test "x$GTK_UPDATE_ICON_CACHE" = "xno"; then
  AC_MSG_ERROR([gtk-update-icon-cache-3.0 or gtk-update-icon-cache not found])
fi

AC_PATH_PROGS([RSVG_CONVERT], [rsvg-convert rsvg], [no])
if test "x$RSVG_CONVERT" = "xno"; then
  AC_MSG_ERROR([rsvg-convert or rsvg is not found, please install librsvg2-bin])
fi

dnl ***************************************************************************
dnl Build dasom-indicator by default
dnl ***************************************************************************

AC_ARG_ENABLE([dasom-indicator],
  AS_HELP_STRING([--disable-dasom-indicator], [Disable dasom-indicator]))

AS_IF([test "x$enable_dasom_indicator" != "xno"],
  [PKG_CHECK_MODULES(APPINDICATOR3, [appindicator3-0.1])])

AM_CONDITIONAL([ENABLE_DASOM_INDICATOR],
               [test "$enable_dasom_indicator" != "no"])

GLIB_GSETTINGS
GOBJECT_INTROSPECTION_CHECK([0.10.1])

AC_OUTPUT([
  Makefile
  agents/Makefile
  agents/gnome-shell-extension/Makefile
  agents/gnome-shell-extension/metadata.json
  agents/app-indicator/Makefile
  data/Makefile
  data/im-config/Makefile
  data/icons/Makefile
  libdasom/Makefile
  libdasom/dasom.pc
  daemon/Makefile
  po/Makefile.in
])
