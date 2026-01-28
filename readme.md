# FM Sound Generator with OPN/OPM interface

```
C++ による FM/PSG 音源の実装です。
AY8910, YM2203, YM2151, YM2608, YM2610 相当のインターフェースも実装してあります。

Copyright (C) by cisc 1998, 2003.

(readme-fmgem.txtより抜粋)
```

## このフォークについて

- [kichikuou氏のリポジトリ](https://github.com/kichikuou/fmgen)ベース
- CMake で共有ライブラリを作るように変更
- セグメンテーションフォルトを引き起こす可能性のある箇所を修正
  - OPNB::ch[6] をコメントアウト (OPNABase で既に定義されている)
- ブリッジインターフェイス( C 関数エクスポート)を追加
- ブリッジインターフェイス呼び出しテストプログラム追加

### ビルドについて
```
mkdir build
cd build 
cmake ../
cmake --build . --config Release
```

### ライセンスについて
- fmgen に関しては readme-fmgen.txt に記載のライセンスに準じます
- フォーク元のコードに関してはそのライセンスに準じます
- このフォークオリジナルの部分に関しては[WTFPL](https://www.wtfpl.net/)とします
