#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>  

// Variaveis para controles de navegacao
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat rotArm1,rotArm2,rotLeg1,rotLeg2, tRot;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini, rot_pingu,Cx,Cy;
int x_ini, y_ini, bot, tx,ty,tz, Atx, Aty, Atz, ArotArm1,ArotArm2,ArotLeg1,ArotLeg2, angH;
GLfloat deslocamentoX, deslocamentoY, deslocamentoZ,movElevator; //movimento
bool arrowFlag, armFlag, legFlag, tFlag, A_armFlag, A_legFlag, AtFlag, MFlag, view, play,win,lose,eMov;
float movArrow;
GLuint idTextura;

// Tamanho e posicao inicial do quadrado
GLfloat x1 = 100.0f;
GLfloat y1 = 150.0f;
GLsizei rsize = 50;

// Tamanho do incremento nas direcoes x e y
// (numero de pixels para se mover a cada
// intervalo de tempo)
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;

void DefineIluminacao(void)
{
	GLfloat luzAmbiente[4] = {0.25, 0.25, 0.25, 1.0}; //TONALIDADE DA COR
	GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0};	  // "cor"
	GLfloat posicaoLuz0[4] = {0.0, 80.0, 0.0, 1.0};   //BRANCO
	GLfloat posicaoLuz1[4] = {0.0, -80.0, 0.0, 1.0};


	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parametros da luz de numero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz0);

	// Define os parametros da luz de numero 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);

	//TRANSPARENCIA
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
}

void Background(void)
{
	//Plataformas
	glColor3f(0.84f, 0.7f, 0.0f);
	glPushMatrix();
		glScalef(1.0, 0.02, 0.5);
		glTranslatef(0.0f, 0.0f, 0.0f);
		glutSolidCube(100);

		glTranslatef(0.0f, 400.0f, 0.0f);
		glutSolidCube(100);

		glTranslatef(0.0f, 400.0f, 0.0f);
		glutSolidCube(100);

		glTranslatef(0.0f, 400.0f, 0.0f);
		glutSolidCube(100);
	glPopMatrix();

	glPushMatrix();
		glScalef(1.0, 1.0, 0.5);
		glTranslatef(0.0f,-50.0f,0.0f);
		glutSolidCube(100);
	glPopMatrix();

	//Elevador 
	glColor3f(0.03f, 0.25f, 0.07f);
	glPushMatrix();
		glScalef(0.02, 1.0, 0.04);
		glTranslatef(150.0f, -26.0f, 400.0f);
		glRotatef(90, 0, 1, 0);
		glutSolidCube(100);

		glTranslatef(0.0f, 0.0f, -250.0f);
		glutSolidCube(100);
	glPopMatrix();

	//Fundo
	glColor3f(0.0f, 0.53f, 0.0f);
	glPushMatrix();
		glScalef(0.91, 1.0, 0.5);
		glTranslatef(0.0f, -29.5f, -50.0f);
		glutSolidCube(110);
	glPopMatrix();

	//Bancos - Andar Terreo
	glColor3f(0.2f, 0.27f, 0.46f);
	glPushMatrix();
		glScalef(1.0, 0.5, 0.5);
		glTranslatef(20.0f, 3.0f, 30.0f);
		glRotatef(0, 0, 1, 0);
		glutSolidCube(5);

		glTranslatef(-40.0f, 0.0f, 0.0f);
		glRotatef(0, 0, 1, 0);
		glutSolidCube(5);

		glTranslatef(60.0f, 0.0f, 0.0f);
		glRotatef(0, 0, 1, 0);
		glutSolidCube(5);

		glTranslatef(-70.0f, 16.0f, 0.0f);
		glRotatef(0, 0, 1, 0);
		glutSolidCube(5);
	glPopMatrix();

	//Seta - Andar Terreo
	glColor3f(0.82f, 0.04f, 0.035f);
	glPushMatrix();
		glTranslatef(-42.0f,3.5f+movArrow,20.0f);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(1.5,2.5,20,20);

		glTranslatef(0.0f,0.0f,-0.75f+movArrow);
		glScalef(0.4, 0.4, 1.0);
		glutSolidCube(2);
	glPopMatrix();

	//Colunas - 2 Andar
	glColor3f(0.65f, 0.65f, 0.65f);
	glPushMatrix();
		glScalef(0.2, 1.0, 0.2);
		glTranslatef(40.0f, 12.0f, 60.0f);
		glRotatef(0, 0, 1, 0);
		glutSolidCube(8);

		glTranslatef(60.0f, 0.0f, 0.0f);
		glRotatef(0, 0, 1, 0);
		glutSolidCube(8);

		glTranslatef(-140.0f, 0.0f, 0.0f);
		glRotatef(0, 0, 1, 0);
		glutSolidCube(8);

		glTranslatef(-60.0f, 0.0f, 0.0f);
		glRotatef(0, 0, 1, 0);
		glutSolidCube(8);
	glPopMatrix();

	//Seta - Segundo Andar
	glColor3f(0.82f, 0.04f, 0.035f);
	glPushMatrix();
		glTranslatef(42.0f,11.5f+movArrow,20.0f);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(1.5,2.5,20,20);

		glTranslatef(0.0f,0.0f,-0.75f+movArrow);
		glScalef(0.4, 0.4, 1.0);
		glutSolidCube(2);
	glPopMatrix();

	//Bancos - 3 Andar
	glColor3f(0.2f, 0.27f, 0.46f);
	glPushMatrix();
		glScalef(1.0, 0.5, 0.5);
		glTranslatef(20.0f, 36.0f, 30.0f);
		glRotatef(0, 0, 1, 0);
		glutSolidCube(5);

		glTranslatef(-40.0f, 0.0f, 0.0f);
		glRotatef(0, 0, 1, 0);
		glutSolidCube(5);

		glTranslatef(60.0f, 0.0f, 0.0f);
		glRotatef(0, 0, 1, 0);
		glutSolidCube(5);
	glPopMatrix();

	//Seta - Terceiro Andar
	glColor3f(0.82f, 0.04f, 0.035f);
	glPushMatrix();
		glTranslatef(-42.0f,19.5f+movArrow,20.0f);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(1.5,2.5,20,20);

		glTranslatef(0.0f,0.0f,-0.75f+movArrow);
		glScalef(0.4, 0.4, 1.0);
		glutSolidCube(2);
	glPopMatrix();	
}

void helicoptero()
{
	//corpo
	glColor3f(0.22f, 0.34f, 0.039f);
	glPushMatrix();
		glTranslatef(0.0f,0.0f,0.0f);
		glScalef(1.0f,0.6f,0.6f);
		glutSolidCube(8);

		glTranslatef(6.0f,0.0f,0.0f);
		glScalef(1.0f,0.4f,0.4f);
		glutSolidCube(8);
	glPopMatrix();

	
	glPushMatrix();
		glColor4f(0.51f, 0.94f, 0.89f,0.5f);
		glTranslatef(-2.5f,0.0f,0.0f);
		glScalef(0.5f,0.4f,0.8f);		
		glutSolidCube(8);
	glPopMatrix();

	//corda
	glColor3f(0.91f, 0.75f, 0.039f);
	glPushMatrix();
		glTranslatef(0.0f,-4.0f,0.0f);
		glScalef(0.05f,1.0f,0.05f);
		glutSolidCube(10);
	glPopMatrix();

	//cauda
	glPushMatrix();
	glColor3f(0.19f, 0.19f, 0.19f);
		glTranslatef(9.0f,0.0f,-2.0f);
		glRotatef(45+angH,0,0,1);
		glScalef(1.0f,0.2f,0.2f);
		glutSolidCube(5);
	glPopMatrix();

	
	glPushMatrix();
	glColor3f(0.19f, 0.19f, 0.19f);
		glTranslatef(9.0f,0.0f,-2.0f); 
		glRotatef(-45+angH,0,0,1);
		glScalef(1.0f,0.2f,0.2f);
		glutSolidCube(5);
	glPopMatrix();

	//base
	glColor3f(0.19f, 0.19f, 0.19f);
	glPushMatrix();
		glScalef(0.2f,1.0f,0.2f);
		glTranslatef(-14.0f,-2.5f,8.0f); 
		glutSolidCube(2);

		glTranslatef(0.0f,0.0f,-17.0f); 
		glutSolidCube(2);

		glTranslatef(31.0f,0.0f,0.0f); 
		glutSolidCube(2);

		glTranslatef(0.0f,0.0f,17.0f); 
		glutSolidCube(2);
	glPopMatrix();

	glPushMatrix();
		glScalef(1.0f,0.1f,0.1f);
		glTranslatef(0.0f,-34.0f,15.0f); 
		glutSolidCube(8);

		glTranslatef(0.0f,0.0f,-32.0f); 
		glutSolidCube(8);
	glPopMatrix();

	//helice
	glPushMatrix();
		glTranslatef(0.0f,0.0f,0.0f);
		glScalef(0.05f,1.0f,0.05f);
		glutSolidCube(8);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f,3.5f,0.0f);
		glRotatef(angH,0,1,0);
		glScalef(1.0f,0.05f,0.05f);
		glutSolidCube(12);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0f,3.5f,0.0f);
		glRotatef(90+angH,0,1,0);
		glScalef(1.0f,0.05f,0.05f);
		glutSolidCube(12);
	glPopMatrix();
}

void escada()
{
	int i=0;
	glColor3f(0.19f, 0.19f, 0.19f);
	glPushMatrix();
		glScalef(1.0f,0.8f,1.0f);
		glTranslatef(0.0f,0.0f,0.0f);
		glutSolidCube(5);

		glTranslatef(2.5f,2.5f,0.0f);
		glutSolidCube(5);

		glTranslatef(2.5f,2.5f,0.0f);
		glutSolidCube(5);

		glTranslatef(2.5f,2.5f,0.0f);
		glutSolidCube(5);
			
		glTranslatef(2.5f,2.5f,0.0f);
		glutSolidCube(5);

		glTranslatef(2.5f,2.5f,0.0f);
		glutSolidCube(5);

		glTranslatef(2.5f,2.5f,0.0f);
		glutSolidCube(5);

		glTranslatef(2.5f,2.5f,0.0f);
		glutSolidCube(5);

		glTranslatef(2.5f,2.5f,0.0f);
		glutSolidCube(5);

		glTranslatef(2.5f,2.5f,0.0f);
		glutSolidCube(5);

		glTranslatef(0.0f,0.2f,0.0f);
		glutSolidCube(5);
	glPopMatrix();
}

void elevator()
{
	glPushMatrix();
		glColor4f(0.69f, 0.69f, 0.69f,1.0f);
		glTranslatef(0.5f, -5.5f, 0.5f);
		glScalef(0.75f,1.0,0.75);
		glutSolidCube(5);
	glPopMatrix();
}

void personThief (void)
{
	//chapeu
	glColor3f(0.97f, 0.97f, 0.97f);
	glPushMatrix();
		glScalef(1.0f,0.5f,1.0f);
		glTranslatef(0.0f,0.0f,0.0f);
		glutSolidCube(5);
	glPopMatrix();

	//head
	glColor3f(0.98f, 0.76f, 0.34f);
	glPushMatrix();
		glScalef(0.9f,0.9f,0.9f);
		glTranslatef(0.0f,-3.5f,0.0f);
		glutSolidCube(5);

		glScalef(0.8f,0.5f,0.6f);
		glTranslatef(0.0f,1.5f,4.0f);
		glutSolidCube(3.5);
	glPopMatrix();

	//corpo
	glColor3f(0.97f, 0.97f, 0.97f);
	glPushMatrix();
		glScalef(0.8f,1.0f,0.6f);
		glTranslatef(0.0f,-8.5f,0.0f);
		glutSolidCube(8);
	glPopMatrix();
}

void armThief()
{
	//ombro
	glColor3f(0.97f, 0.97f, 0.97f);
	glPushMatrix();		
		glTranslatef(1.2f,0.0f,0.0f);
		glutSolidSphere(1,20,20); //raio, poligonos, diametro

		glTranslatef(0.0f,-5.0f,0.0f); 
		glutSolidSphere(1,20,20); //raio, poligonos, diametro

		glColor3f(0.98f, 0.76f, 0.34f);
		glTranslatef(0.0f,-3.5f,3.4f); 
		glutSolidSphere(1,20,20); //raio, poligonos, diametro
	glPopMatrix();

	glColor3f(0.97f, 0.97f, 0.97f); 
	glPushMatrix();	
		glScalef(0.2f,1.0f,0.25f);
		glTranslatef(6.0f,-2.0f,0.0f);
		glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90,0,1,0);
		glRotatef(-45,0,0,1);
		glScalef(1.0f,0.25f,0.2f);
		glTranslatef(6.0f,-15.0f,-6.0f);
		glutSolidCube(5);
	glPopMatrix();
}

void legsThief()
{
	glColor3f(0.97f, 0.97f, 0.97f);
	glPushMatrix();
		glTranslatef(3.0f,-8.0f,0.2f);
		glutSolidSphere(1.5,20,20);
	glPopMatrix();

	glPushMatrix();
		glScalef(0.2f,0.6f,0.2f);
		glTranslatef(15.0f,-17.5f,1.0f);
		glutSolidCube(10);

		glScalef(1.0f,0.2f,1.0f);
		glTranslatef(0.0f,-20.0f,5.0f);
		glutSolidCube(10);
	glPopMatrix();
}

void personPolice(void)
{
	//chapeu
	glColor3f(0.10f, 0.10f, 0.10f);
	glPushMatrix();
		glScalef(1.0f,0.5f,1.0f);
		glTranslatef(0.0f,0.0f,0.0f);
		glutSolidCube(5);

		glScalef(1.0f,0.8f,1.0f);
		glTranslatef(0.0f,5.0f,0.0f);
		glutSolidCube(4);

		glScalef(0.8f,1.0f,0.8f);
		glTranslatef(0.0f,3.0f,0.0f);
		glutSolidCube(3);
	glPopMatrix();

	//head
	glColor3f(0.98f, 0.76f, 0.34f);
	glPushMatrix();
		glScalef(0.9f,0.9f,0.9f);
		glTranslatef(0.0f,-3.5f,0.0f);
		glutSolidCube(5);

		glScalef(0.8f,0.5f,0.6f);
		glTranslatef(0.0f,1.5f,4.0f);
		glutSolidCube(3.5);

		glColor3f(0.74f, 0.48f, 0.0f);
		glScalef(0.8f,0.5f,0.6f);
		glTranslatef(0.0f,-3.8f,0.8f);
		glutSolidCube(3.5);
	glPopMatrix();

	//corpo
	glColor3f(0.28f, 0.23f, 0.76f);
	glPushMatrix();
		glScalef(0.8f,1.0f,0.6f);
		glTranslatef(0.0f,-8.5f,0.0f);
		glutSolidCube(8);
	glPopMatrix();
}

void armPolice()
{
	//ombro
	glColor3f(0.28f, 0.23f, 0.76f);
	glPushMatrix();		
		glTranslatef(1.2f,0.0f,0.0f);
		glutSolidSphere(1,20,20); //raio, poligonos, diametro

		glTranslatef(0.0f,-5.0f,0.0f);
		glutSolidSphere(1,20,20); //raio, poligonos, diametro

		glColor3f(0.98f, 0.76f, 0.34f);
		glTranslatef(0.0f,-3.5f,3.4f);
		glutSolidSphere(1,20,20); //raio, poligonos, diametro
	glPopMatrix();

	glColor3f(0.28f, 0.23f, 0.76f); 
	glPushMatrix();	
		glScalef(0.2f,1.0f,0.25f);
		glTranslatef(6.0f,-2.0f,0.0f);
		glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90,0,1,0);
		glRotatef(-45,0,0,1);
		glScalef(1.0f,0.25f,0.2f);
		glTranslatef(6.0f,-15.0f,-6.0f);
		glutSolidCube(5);
	glPopMatrix();
}

void legsPolice()
{
	glColor3f(0.28f, 0.23f, 0.76f);
	glPushMatrix();
		glTranslatef(3.0f,-8.0f,0.2f);
		glutSolidSphere(1.5,20,20);
	glPopMatrix();

	
	glPushMatrix();
		glColor3f(0.28f, 0.23f, 0.76f);
		glScalef(0.2f,0.6f,0.2f);
		glTranslatef(15.0f,-17.5f,1.0f);
		glutSolidCube(10);


		glColor3f(0.1f, 0.1f, 0.1f);
		glScalef(1.0f,0.2f,1.0f);
		glTranslatef(0.0f,-20.0f,5.0f);
		glutSolidCube(10);
	glPopMatrix();
}

void Ladrao()
{
	glPushMatrix();
		glTranslatef(5.0f, 5.5f, 0.0f);
		personThief();
	glPopMatrix();

	//Animar Braco
	glPushMatrix();
		glRotatef(ArotArm1, 1, 0, 0);
		glTranslatef(0.0f, 0.0f, 0.0f);
		armThief();
	glPopMatrix();

	glPushMatrix();
		glRotatef(ArotArm2, 1, 0, 0);
		glTranslatef(7.5f, 0.0f, 0.0f);
		armThief();
	glPopMatrix();
	//Animar Perna
	glPushMatrix();
		glRotatef(ArotLeg1, 1, 0, 0);
		glTranslatef(0.0f, 0.0f, 0.0f);
		legsThief();
	glPopMatrix();

	glPushMatrix();
		glRotatef(ArotLeg2, 1, 0, 0);
		glTranslatef(4.0f, 0.0f, 0.0f);
		legsThief();
	glPopMatrix();

}

void Policia()
{
	glPushMatrix();
		glTranslatef(5.0f, 5.5f, 0.0f);
		personPolice();
	glPopMatrix();

	//Animar Braco
	glPushMatrix();
		glRotatef(rotArm1, 1, 0, 0);
		glTranslatef(0.0f, 0.0f, 0.0f);
		armPolice();
	glPopMatrix();

	glPushMatrix();
		glRotatef(rotArm2, 1, 0, 0);
		glTranslatef(7.5f, 0.0f, 0.0f);
		armPolice();
	glPopMatrix();
	//Animar Perna
	glPushMatrix();
		glRotatef(rotLeg1, 1, 0, 0);
		glTranslatef(0.0f, 0.0f, 0.0f);
		legsPolice();
	glPopMatrix();

	glPushMatrix();
		glRotatef(rotLeg2, 1, 0, 0);
		glTranslatef(4.0f, 0.0f, 0.0f);
		legsPolice();
	glPopMatrix();
}

void DesenhaTexto(void *font, char *string) 
{  
	// Exibe caractere a caractere
	while(*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++); 
}

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Chama a funcao que especifica os parametros de iluminacao
	DefineIluminacao();

	//Background
	glPushMatrix();
		glTranslatef(0.0f, -25.0f, 0.0f);
		Background();
	glPopMatrix();

	//Elevador
	glPushMatrix();
		glTranslatef(0.0f, 0.0f+movElevator, 16.0f);
		elevator();
	glPopMatrix();

	//Personagem - Ladrao
	glPushMatrix();
		glScalef(0.25f,0.25f,0.25f);
		glTranslatef(Atx+80.0f, Aty+(-50.5f), Atz+84.0f); //IMPORTANTE: -85.2 -> DISTANCIA PRO TERREO
		if(AtFlag==true)
			glRotatef(90,0,1,0);
		else
		glRotatef(-90,0,1,0);
		Ladrao();
	glPopMatrix();

	//Personagem - Policia
	glPushMatrix();
		glScalef(0.25f,0.25f,0.25f);
		glTranslatef(tx+80.0f, ty+(-82.5f), tz+84.0f); //IMPORTANTE: -85.2 -> DISTANCIA PRO TERREO
		if(tFlag==true)
			glRotatef(90,0,1,0);
		else
			glRotatef(-90,0,1,0);
		Policia();
	glPopMatrix();
	

	//Escadas
	glPushMatrix();
		glScalef(0.4f,0.4f,0.4f);
		glTranslatef(-80.0f,-60.0f,50.0f);
		glRotatef(180,0,1,0);
		escada();

		glTranslatef(0.0f,0.0f,-5.2f);
		escada();
	glPopMatrix();

	glPushMatrix();
		glScalef(0.4f,0.4f,0.4f);
		glTranslatef(80.0f,-40.0f,50.0f);
		escada();

		glTranslatef(0.0f,0.0f,-5.2f);
		escada();
	glPopMatrix();

	glPushMatrix();
		glScalef(0.4f,0.4f,0.4f);
		glTranslatef(-80.0f,-20.0f,50.0f);
		glRotatef(180,0,1,0);
		escada();

		glTranslatef(0.0f,0.0f,-5.2f);
		escada();
	glPopMatrix();

	//Fuga
	glPushMatrix();
		glTranslatef(40.0f,12.0f,22.0f);
		glRotatef(180,0,1,0);
		helicoptero();
	glPopMatrix();

	//Textos
	glPushMatrix();	
		glTranslatef(-45,20,10);
		glScalef(0.02, 0.02, 0.02); // diminui o tamanho do fonte	
		glLineWidth(3); // define a espessura da linha
		DesenhaTexto(GLUT_STROKE_ROMAN,"F1/F2 - Mudar Visao    F3 - Iniciar Jogo    ESC - Sair");
	glPopMatrix();

	if(win)
	{
		glColor3f(0.023f,0.73f,0.0f);
		glPushMatrix();	
			glTranslatef(-5,10,20);
			glScalef(0.05, 0.05, 0.05); // diminui o tamanho do fonte	
			glLineWidth(3); // define a espessura da linha
			DesenhaTexto(GLUT_STROKE_ROMAN,"Vitoria");
		glPopMatrix();
	}
	if(lose)
	{
		glColor3f(1.0f, 0.00f, 0.0f);
		glPushMatrix();	
			glTranslatef(-20,10,20);
			glScalef(0.02, 0.02, 0.02); // diminui o tamanho do fonte	
			glLineWidth(3); // define a espessura da linha
			DesenhaTexto(GLUT_STROKE_ROMAN,"O ladrao fugiu! Tente novamente");
		glPopMatrix();
	}
	// Executa os comandos OpenGL
	glutSwapBuffers();
}


// Funcao usada para especificar a posicao do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	DefineIluminacao();
	// Posiciona e orienta o observador
	glTranslatef(-obsX, -obsY, -obsZ);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);

	if(view)gluLookAt(0,0,0.5,0,0,0,0,1,0);
	else gluLookAt(-18.199999+Cx,-19.40003+Cy,20.0300001, // onde ta a cabeca, MEXE APENAS EM X
				   -60.199999+Cx,-20.40003+Cy,10.0300001, // pra onde ele ta olhando 
				   0,1,0);
}

void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projecao
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projecao
	glLoadIdentity();

	// Especifica a projecao perspectiva
	// (angulo, aspecto, zMin, zMax)
	gluPerspective(angle, fAspect, 0.5, 1000);

	PosicionaObservador();

	// Especifica posicao do observador, do alvo e do vetor up
	
}

// Funcao callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado(unsigned char tecla, int x, int y)
{
	if (tecla == 27) // ESC ?
		exit(0);
}

void movChar()
{
	if(armFlag && rotArm1<45)
	{
		rotArm1 +=5;
		rotArm2 -=5;
	}
	else
	{
		rotArm1 -=5;
		rotArm2 +=5;
	}
	if(legFlag && rotLeg1<12)
	{
		rotLeg1 +=4;
		rotLeg2 -=4;
	}
	else
	{
		rotLeg1 -=2;
		rotLeg2 +=2;
	}
	
	if(rotArm1==45)
		armFlag=false;
	if(rotArm1==-45)
		armFlag=true;

	if(rotLeg1==12)
		legFlag=false;
	if(rotLeg1==-12)
		legFlag=true;
}

// Funcao callback para tratar eventos de teclas especiais
void TeclasEspeciais(int tecla, int x, int y)
{
	switch (tecla)
	{
	case GLUT_KEY_HOME:
		if (angle >= 10)
			angle -= 5;
		break;
	case GLUT_KEY_END:
		if (angle <= 150)
			angle += 5;
		break;
		break;
	case GLUT_KEY_LEFT: // desloca o volume de visualizacao para o lado esquerdo
		if(play)
		{
			tFlag=false;
			if(tx>-255)
			{
				tx -= 1;
				Cx -= 0.4;
			}	
			movChar();
			if((tx>-234 && tx<-200)  && ((ty>=0 && ty<=32) || (ty>=65 && ty<=96)))
			{
				ty++; //escada da esquerda
				Cy += 0.3;
			}
		}
		
		break;
	case GLUT_KEY_RIGHT: // desloca o volume de visualizacao para o lado direito
		if(play)
		{
			if(tx<98)
			{
				tx += 1;
				Cx +=0.4;
			}
			tFlag=true;
			movChar();
			if(tx>42 && tx<75 && (ty>=32 && ty<=64))
			{
				Cy += 0.3;
				ty++; // escada da direita
			}
		}
		break;
	case GLUT_KEY_F1: //mudar view
		view=true;
		break;
	case GLUT_KEY_F2: //mudar view
		view=false;
		break;
	case GLUT_KEY_F3:
		play=true;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Funcao callback para eventos de botoes do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		// Salva os parametros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else
		bot = -1;
}

// Funcao callback para eventos de movimento do mouse
#define SENS_ROT 5.0
#define SENS_OBS 10.0
#define SENS_TRANSL 10.0
void GerenciaMovim(int x, int y)
{
	// Botao esquerdo ?
	if (bot == GLUT_LEFT_BUTTON)
	{
		// Calcula diferencas
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica angulos
		rotY = rotY_ini - deltax / SENS_ROT;
		rotX = rotX_ini - deltay / SENS_ROT;
	}
	// Botao direito ?
	else if (bot == GLUT_RIGHT_BUTTON)
	{
		// Calcula diferenca
		int deltaz = y_ini - y;
		// E modifica distancia do observador
		obsZ = obsZ_ini + deltaz / SENS_OBS;
	}
	// Botao do meio ?
	else if (bot == GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferencas
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posicoes
		obsX = obsX_ini + deltax / SENS_TRANSL;
		obsY = obsY_ini - deltay / SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Funcao callback chamada quando o tamanho da janela foi alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisao por zero
	if (h == 0)
		h = 1;

	// Especifica as dimensoes da viewport
	glViewport(0, 0, w, h);

	// Calcula a correcao de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

void AnimaPrincipal(int value)
{
	if(play)
	{
		if(MFlag==true)Atx++;
		if(MFlag==false)Atx--;

		if(Atx==98)
		{
			MFlag=false;
			AtFlag=false;
		}
		if(Atx==-255)
		{
			MFlag=true;
			AtFlag=true;
		}
	
		if((Atx>42 && Atx<75) && (Aty>=0 && Aty<32))Aty++; // escada da direita
		if(Atx>-234 && Atx<-200 && (Aty>=32 && Aty<=63))Aty++; //escada da esquerda tem q colocar o da escada debaixo tbm
	
		if(A_armFlag && ArotArm1<45)
		{
			ArotArm1 +=5;
			ArotArm2 -=5;
		}
		else
		{
			ArotArm1 -=5;
			ArotArm2 +=5;
		}
		if(A_legFlag && ArotLeg1<12)
		{
			ArotLeg1 +=4;
			ArotLeg2 -=4;
		}
		else
		{
			ArotLeg1 -=2;
			ArotLeg2 +=2;
		}
	
		if(ArotArm1==45)A_armFlag=false;
		if(ArotArm1==-45)A_armFlag=true;

		if(ArotLeg1==12)A_legFlag=false;
		if(ArotLeg1==-12)A_legFlag=true;


		if(Atx==tx && Aty==(ty-33)) //colisao de vitoria
		{
			win=true;	
			play=false;
		}
		if(Aty==64 && Atx==80) //colisao derrota
		{
			lose=true;
			play=false;
		}
		angH+=5;
	}	
	glutPostRedisplay();
	glutTimerFunc(60, AnimaPrincipal, 1); //colocar uma animacao no ladrao
}

void AnimaSec(int value)
{
	if(play)
	{
		if(arrowFlag && movArrow<4) movArrow +=0.25;
		else movArrow -=0.25;
		
		if(movArrow==1)arrowFlag=false;
		if(movArrow==0)arrowFlag=true;


		if(eMov && movElevator>-16.0)movElevator-=0.5;
		else movElevator+=0.5;

		if(movElevator==-16.0)eMov=false;
		if(movElevator==0.0)eMov=true;
	}	
	glutPostRedisplay();
	glutTimerFunc(90, AnimaSec, 1); //colocar uma animacao no ladrao
}

void Inicializa(void)
{
	glClearColor(0.47f, 0.47f, 0.47f, 1.0f);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);

	//Inicializa a variavel com o angulo de projecao
	angle = 30;

	//Demais variaveis
	rotX = 0;
	rotY = 0;
	obsY = 0;
	obsX = 0;
	obsZ = 122;
	deslocamentoX = 0.0f;
	deslocamentoY = 0.0f;
	deslocamentoZ = 0.0f;

	//Movimento dos Bracos
	rotArm1 = 0;
	rotArm2 = 0;
	rotLeg1 = 0;
	rotLeg2 = 0;
	armFlag = true;
	legFlag = true;
	tFlag = true;
	tRot=0;
	Atx=0;Aty=0;Atz=0;
	tx=0;ty=0;tz=0;
	ArotArm1=0,ArotArm2=0,ArotLeg1=0,ArotLeg2=0;
	A_armFlag=true, A_legFlag=true;
	AtFlag=true;
	MFlag=true;
	view=true;
	Cx=0,Cy=0;
	play=false;
	arrowFlag=true;
	movArrow=0.0f;
	angH=0;
	win=false,lose=false;
	movElevator=0.0f,eMov=true;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(5, 5);
	glutInitWindowSize(650, 380); // definir
	glutCreateWindow("Keystone Kapers 3D");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a funcao callback para tratamento das teclas normais
	glutKeyboardFunc(Teclado);

	// Registra a funcao callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a funcao callback para eventos de botoes do mouse
	glutMouseFunc(GerenciaMouse);

	// Registra a funcao callback para eventos de movimento do mouse
	glutMotionFunc(GerenciaMovim);

	glutTimerFunc(60,AnimaPrincipal,1);
	glutTimerFunc(70,AnimaSec,1);
	Inicializa();
	glutMainLoop();
	
	return 0;
}