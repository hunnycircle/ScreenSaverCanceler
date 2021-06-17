# ScreenSaverCanceler

スクリーンセーバーが動き出すのをMOUSE MOVEで抑止する。

# Features

なぜかスクリーンセーバーを短めの時間で設定しなければならない人向け。

# Requirement

* Microsoft Windows 10
* たぶん [Visual Studio 2019 の Microsoft Visual C++ 再頒布可能パッケージ（x86）](https://visualstudio.microsoft.com/ja/downloads/) が必要

# Installation

ssc.exeをダウンロードして実行してください。

# Usage

ssc.exeを実行するとタスクトレイに常駐します。一定間隔でマウスを動かしたことにしてScreen Saverが動くのを抑止します。

タスクトレイのアイコンを左クリックしてON、OFFを切り替えられます。

起動時パラメタでintervalを分指定できます。省略値は3（3分）です。

ex. ssc.exe 5

# Author

はに〇 <hunny@tea.nifty.jp>

# License

MIT License
