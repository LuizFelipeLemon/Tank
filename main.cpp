#include "sfml.h"
#include "util.h"
#include<cmath>
#define tam 100
using namespace util;

struct Coordenada
{
    float x, y;
};

struct Tanque
{
    Coordenada c;
    bool atirando;
};

struct Tiro
{
    Coordenada c;
};

void desenhaTanque(SFML& sfml, Tanque tanque)
{
    int points[][2] =
    {
        {20,40},{0,-20},{-20,40},{0,20}
    };
    sfml.convexPolygon(tanque.c.x,tanque.c.y,points,4);
}
int tela = 0;
int vidas = 3;
int nivel = 1;
int i;

char frase[200];
char vida[200];
char niveis[200];
int pontos = 0;

float enemyX = random(20, 330);
float enemyY = random(0, 1);

bool podeMudar = true;

float estrelasX[tam];
float estrelasY[tam];
float estrelasVel[tam];
float estrelasTam[tam];

int qtEstrelas = 50;

int main()
{
    //cria a janela com tamanho 640x480 pixels
    SFML sfml(640,480,"Meu jogo!");

    //define a cor de fundo como preto
    sfml.background(0,0,0);

    // desenha objetos
  for(i = 0; i < qtEstrelas; i++) {
	  sfml.rect(estrelasX[i],estrelasY[i],estrelasTam[i],estrelasTam[i]);
  }

  // movimenta objetos
  for(i = 0; i < qtEstrelas; i++) {
	  estrelasY[i] = estrelasY[i] + estrelasVel[i];
	  if (estrelasY[i] > 480) {
		estrelasX[i] = random(0,640);
		estrelasY[i] = -random(0,480);
	  }
  }

    Tanque tanque;
    tanque.c.x = 320;
    tanque.c.y = 430;
    tanque.atirando = false;

    Image imagem("tanque.jpg");

    Tiro tiro;

    enemyY+=0.5;

    for (i = 0; i < qtEstrelas; i++) {
		estrelasX[i] = random(0,640);
		estrelasY[i] = random(0,480);
		estrelasVel[i] = 2+random(0,10)/10;
		estrelasTam[i] = random(2,4);
	}

    //início do laço principal do jogo
    while (sfml.windowIsOpen())
    {

        //apaga o conteúdo da janela
        sfml.clear();

        if(tela == 0)
        {
            //define a cor de fundo como preto
            sfml.background(0,0,0);
            sfml.image(imagem, 150, 150);
            sfml.text("TANK GAME", 150, 200);
            sfml.text("Start Game Press Enter", 150, 230);
            sfml.text("Quit", 150, 250);
        }

        if(sfml.keyIsDown(SFML::Key::Enter))
        {
            tela = 1;
        }

        if(tela == 1)
        {
            //Desenha uma ellipse no centro da tela
            if(sfml.keyIsDown(SFML::Key::Left))
            {
                tanque.c.x -= 2;
                if(tanque.c.x <= 36)
                {
                    tanque.c.x += 2;
                }
            }
            else if(sfml.keyIsDown(SFML::Key::Right))
            {
                tanque.c.x += 2;
                if(tanque.c.x >= 367)
                {
                    tanque.c.x -= 2;
                }
            }
            else if(sfml.keyIsDown(SFML::Key::Space))
            {
                if(!tanque.atirando)
                {
                    tanque.atirando = true;
                    tiro.c.x = tanque.c.x-1;
                    tiro.c.y = tanque.c.y-2;
                }
            }

            desenhaTanque(sfml,tanque);
            enemyY+= 0.5;

            if(tanque.atirando)
            {
                sfml.ellipse(tiro.c.x, tiro.c.y,10,10);
                tiro.c.y -= 6;
                if(tiro.c.y < 0-10)
                {
                    tanque.atirando = false;
                }
            }

            //desenha os limites do jogo
            sfml.line(10, 1, 10, 560);
            sfml.line(400, 1, 400, 560);

            //Define o tamanho da fonte
            sfml.textSize(16);
            //cria a frase que ser� desenhada no vetor de caracteres frase.
            sprintf(frase,"Monstros destruidos: %d ",pontos);
            //escreve a frases na tela
            sfml.text(frase, 445, 190);

            sprintf(vida, "Vidas: %d", vidas);
            sfml.text(vida, 445, 230);

            //Texto com o nivel
            sfml.textSize(16);
            sprintf(niveis,"Nivel: %d ",nivel);
            sfml.text(niveis, 445, 270);

            //Define o tamanho da fonte
            sfml.textSize(35);
            sfml.text("TANK GAME", 430, 120);

            //Detectar colisao
            bool isColliding = (dist(tiro.c.x+25,tiro.c.y+25,enemyX+20,enemyY+20) < 25+25) ? true : false;

            if(!isColliding)
            {
                tiro.c.y += 0.5;
                enemyY+=0.5;
            }
            else
            {

                sfml.text("Colidiu!", 455, 400);
                pontos++;

                enemyX = random(12,360);
                enemyY = random(0,1);
                podeMudar = true;
            }

            bool isColliding_vidas = (dist(tanque.c.x+25,tanque.c.y+25,enemyX+20,enemyY+20) < 25+25) ? true : false;

            if(!isColliding_vidas)
            {
                enemyY += 0.5;
            }
            else
            {
                sfml.text("Colidiu!", 455, 400);
                vidas--;
                enemyX = random(12, 360);
                enemyY = random(0, 1);
            }

            sfml.rect(enemyX, enemyY, 40, 40);

            if(enemyY >= 412)
            {
                enemyX = random(12, 360);
                enemyY = random(0, 1);
            }

            if(pontos >= 6)
            {
                nivel = 2;
                enemyY+=0.8;
            }

            if(pontos >= 10)
            {
                nivel = 3;
                enemyY+=1.0;
            }

            if(pontos >= 17)
            {
                nivel = 4;
                enemyY+=1.2;
            }

            if(pontos >= 25)
            {
                nivel = 5;
                enemyY+=1.6;
            }
        }

        if(pontos == 30 || vidas == 0)
        {
            sfml.clear();
            sfml.fill(255, 255, 255);
            sfml.textSize(55);
            sfml.text("GAME OVER", 150, 200);

        }

      //  tela = 0;

        sfml.display();

    }

    return 0;
}
