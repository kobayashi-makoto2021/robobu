// =============================================
//  page.h  操作画面のHTML
//  R"=====( と )=====" のあいだには、ふつうのHTMLをそのまま書ける。
//  PROGMEM：小さなRAMではなく、大きなフラッシュメモリに入れておく
//
//  スライダーのはじめの値（moveTime）を、PAGE_TOP と PAGE_BOTTOM の
//  あいだに http.h が書きこむ。そのため2つに分けている。
// =============================================
#pragma once

// ---- 前半：見た目の設定（CSS）、ボタン、スライダーの途中まで ----
const char PAGE_TOP[] PROGMEM = R"=====(<!DOCTYPE html>
<html lang="ja">
<head>
<meta charset="UTF-8">
<title>Robot Controller</title>
<link rel="icon" href="data:,">
<style>
body { font-family: sans-serif; text-align: center; background: #eef3f8; color: #1f2d3d; }
.pad { display: grid; grid-template-columns: repeat(3, 90px); grid-template-rows: repeat(3, 90px);
       gap: 10px; justify-content: center; margin: 20px auto; }
.btn { display: flex; align-items: center; justify-content: center; min-width: 90px; height: 90px;
       padding: 0 16px; box-sizing: border-box; font-size: 36px; color: #fff; background: #1e73be;
       border-radius: 16px; text-decoration: none; box-shadow: 0 5px #0d4a80; user-select: none; }
.btn:active { transform: translateY(5px); box-shadow: none; }
.stop { background: #d9534f; box-shadow: 0 5px #a12d2a; }
.row { display: flex; gap: 10px; justify-content: center; margin: 10px; }
input { width: 260px; }
</style>
</head>
<body>
<h1>ロボット操作パネル</h1>

<div class="pad">
  <span></span>                         <a class="btn" href="/M">▲</a>      <span></span>
  <a class="btn" href="/L">◀</a>      <a class="btn stop" href="/E">■</a> <a class="btn" href="/R">▶</a>
  <span></span>                         <a class="btn" href="/B">▼</a>      <span></span>
</div>

<div class="row">
  <!-- ボタンを増やすときは、この下に1行ずつ追加する（ミッションチャレンジ） -->
</div>

<p>1回に動く時間：<b id="t"></b> ミリ秒</p>
<input id="s" type="range" min="100" max="2000" step="100" value=")=====";

// ---- 後半：スライダーの残り ----
const char PAGE_BOTTOM[] PROGMEM = R"=====(" oninput="t.textContent = this.value" onchange="fetch('/T' + this.value)">
<script>t.textContent = s.value;</script>
</body>
</html>
)=====";
