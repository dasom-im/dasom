[![Build Status](https://travis-ci.org/dasom-im/dasom.svg?branch=master)](https://travis-ci.org/dasom-im/dasom)

# Dasom
Dasom is an input method framework, which provides

  * Input Method Server
    * dasom-daemon including XIM

  * Indicators
    * GNOME shell: dasom agent extension
    * KDE, Unity, GNOME panel: dasom-indicator (based on libappindicator3)

Project Homepage: https://github.com/dasom-im/dasom


## LICENSE

  dasom is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published
  by the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  dasom is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program;  If not, see <http://www.gnu.org/licenses/>.


## INSTALL

  * Compile
```bash
    ./autogen.sh
    make
    sudo make install
    sudo ldconfig
    sudo make update-gtk-icon-cache
```
  * For gnome-shell, enable `dasom-agent@gnome-shell-extensions.cogno.org`
```bash
    gnome-shell-extension-tool -e dasom-agent@gnome-shell-extensions.cogno.org
```
  * Configure im-config
```bash
    Run im-config, then select Dasom, logout and login.
```

## Troubleshoot

* Failed to load shared library  
  Check `/etc/ld.so.conf` and `/etc/ld.so.conf.d/` for `/usr/local/lib path`


## Architecture
```

    +- im modules (optional) -+  +---- each process -----+  +- a process --+
    |        dasom-gtk        |  | gnome-shell-extension |  |   X server   |
    |        dasom-qt         |  | dasom-indicator       |  +--------------+
    +-------------------------+  +-----------------------+    ^ |
                 | calls                  | calls             | |
       +------------------+    +---------------------+        | |
       | dasom IM library |    | dasom agent library |        | | communicates
       +------------------+    +---------------------+        | |
                ^ |                      ^ |                  | |
                | |   communicates       | |                  | |
                | |   via Unix Socket    | |                  | |
                | v                      | v                  | v
          +---------------------- a process ----------------------+
          |                     dasom-daemon (including XIM)      |
          +-------------------------------------------------------+
                          | calls                  | create instance
                          | singleton instance     | (not module yet)
                +---------------+            +------------------+
                | engine module |   calls    | candidate module |
                |   interface   | ---------> |    interface     |
                +---------------+            +------------------+
                  |                             |
                  +- dasom-english (embedded)   +- dasom-candidate (gtk3)
                  +- dasom-jeongeum (optional)

```
## References

  http://www.x.org/releases/X11R7.6/doc/libX11/specs/XIM/xim.html  
  http://www.w3.org/TR/ime-api/  
  https://developer.chrome.com/extensions/input_ime  
  https://docs.enlightenment.org/stable/efl/group__Ecore__IMF__Lib__Group.html  
  http://doc.qt.io/qt-4.8/qinputcontext.html  
  http://doc.qt.io/qt-5/qinputmethod.html  
  https://git.gnome.org/browse/gtk+  

  https://github.com/ibus/ibus  
  https://github.com/fcitx/fcitx  
  https://github.com/uim/uim  
