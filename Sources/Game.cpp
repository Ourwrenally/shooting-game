#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)
// TODO: 砲台を青い壁に沿って上下に動かす。(C)
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)
// TODO: スコアのサイズを大きくする。(E)
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)


Vector2 cloudPos;          //!< 雲の位置
Vector2 cannonPos;         //!< 砲台の位置
Vector2 bulletPos;         //!< 弾の位置
Rect    targetRect;        //!< ターゲットの矩形
int     score;             //!< スコア
bool    cannonflag = true; //!< 砲台の上下判定 true:上移動 false:下移動 ((C)実装 HW16A113 多田 亮太)


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    PlayBGM("bgm_maoudamashii_8bit07.mp3");//  (G) hw15a139 中西
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-310, -150);//(A)　hw15a139 中西
    targetRect = Rect(279, -140, 40, 40);//(A)　hw15a139　中西
    bulletPos.x = -999;
    score = 0;
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
    }

    void PlaySE();   //(H) hw15a139 中西
    
    if(Input::GetKeyDown(KeyMask::Space)) {
        PlayBGM("se_maoudamashii_explosion03.mp3");
    }
    
    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 100 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         //(F)　hw15a139中西
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
        }
    }
    if (bulletPos.x > 330) bulletPos.x = -999; //(D)右端に行ったら打てるようになる　HW16A108　相馬亨哉

    
    cloudPos[0]+= 50.0f * Time::deltaTime*15;//雲初期位置&時間(B) hw15a139中西
    
    if (cloudPos[0] > 300) {//雲の復活するまで(B) hw15a139 中西
        cloudPos[0] = -318;                //雲戻る位置。(B)　hw15a139 中西
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);
    if (cannonPos.y <= -140) cannonflag = true;  //砲台が地面に着いたらtrueにする　   ((C)実装 HW16A113 多田 亮太)
    if (cannonPos.y > -70) cannonflag = false;   //砲台がうえに行ったらfalseにする　  ((C)実装 HW16A113 多田 亮太)
    if (cannonflag == true) cannonPos.y+=1;      //cannonflagがtrueなら上に移動する ((C)実装 HW16A113 多田 亮太)
    else cannonPos.y-=1;                         //cannonflagがtrueなら下に移動する ((C)実装 HW16A113 多田 亮太)

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 40.0f);//(E) hw15a139  中西
    DrawText(FormatString("%05d", score), Vector2(-319, 199), Color::black);//(F)　hw15a139　中西
    DrawText(FormatString("%05d", score), Vector2(-320, 200), Color::white);//(F) hw15a139 　中西
}

