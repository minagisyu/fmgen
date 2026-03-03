# FM Sound Generator with OPN/OPM interface

```
C++ による FM/PSG 音源の実装です。
AY8910, YM2203, YM2151, YM2608, YM2610 相当のインターフェースも実装してあります。

Copyright (C) by cisc 1998, 2003.

(fmgen readme.txtより抜粋)
```

## このフォークについて

- [kichikuou氏のリポジトリ](https://github.com/kichikuou/fmgen)ベース
- CMake で共有ライブラリを作るように変更
- ブリッジインターフェイス(C 関数エクスポート)を追加
- ブリッジインターフェイス呼び出しテストプログラム追加
- セグメンテーションフォルトを引き起こす可能性のある箇所を修正
  - OPNB::ch[6] をコメントアウト (OPNABase で既に定義されている)
- 乱数生成を Xorshift32 に変更
  - アルゴリズムを固定化し出力結果を安定させるため
- 未初期化のまま使用していた変数を初期化するように変更
  - 初期値は未定義、環境やコンパイラオプションによって異なる値になっていた
- OPNA::LoadRhythmSample() で環境によって正常に動作していない問題を修正
  - 64bit linux/mac 環境で誤って 4GB のメモリを確保 or ファイルシークしようとする問題を修正
  - 2608_RYM.WAV を探しに行けない問題を修正
  - メモリ解放漏れ修正
  - 不必要にチェックしている部分をコメントアウト

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
