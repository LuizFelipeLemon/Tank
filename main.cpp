#include "sfml.h"
#include "util.h"

using namespace util;

int main()
{

    SFML sfml(640,480,"Meu jogo!");
    sfml.background(165,182,174);

    float xplayer = 190;
    float yplayer = 420;

    int xshot = xplayer+15;
    int yshot = yplayer;
    bool podeMudar = true;

    //Define o tamanho da fonte
    sfml.textSize(16);

    char frase[200];
    int contagem = 0;
    int posX = 0;
    int posY = 200;

    float speed = 5;

    while (sfml.windowIsOpen())
    {

        sfml.clear();
        //   sfml.noFill();

        //desenha um circulo para os disparos
        if(!podeMudar)
        {
            yshot -= 6;
        }

        if(yshot < -20)
        {
            podeMudar = true;
        }

        if(sfml.keyIsDown(SFML:: Key :: Space) && podeMudar)
        {
            xshot = xplayer+15;
            yshot = 400;
            podeMudar = false;
        }

        sfml.fill(0, 0, 0);
        sfml.ellipse(xshot,yshot,20,20);

        //movimento do jogador
        if (sfml.keyIsDown(SFML::Key::Left))
        {
            xplayer -= speed;
            if (xplayer <= 10)
            {
                xplayer+=speed;
            }
        }
        else if (sfml.keyIsDown(SFML::Key::Right))
        {
            xplayer+=speed;
            if(xplayer>=350)
            {
                xplayer-=speed;
            }
        }
        else if (sfml.keyIsDown(SFML::Key::Up))
        {
            yplayer=yplayer;
        }
        else if (sfml.keyIsDown(SFML::Key::Down))
        {
            yplayer=yplayer;
        }

        //desenha os limites do jogo
        sfml.line(10, 1, 10, 560);
        sfml.line(400, 1, 400, 560);

        //desenha o jogador
        sfml.fill(255, 255, 255);
        sfml.rect(xplayer,yplayer, 50, 50);

        // retângulo que representa o quadro de informações
        sfml.rect(360, 110, 360, 220, 90);
        //cria a frase que será desenhada no vetor de caracteres frase.
        sprintf(frase,"Já derotou %d naves",contagem);

        //escreve a frase na tela
        sfml.text(frase, 550, 95);

        if (posX < 640){
            posX = posX + 5;
        }else{
            contagem++;
            posX = 0;
        }

        sfml.display();

    }

    return 0;
}
