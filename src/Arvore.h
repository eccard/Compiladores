#ifndef ARVORE_H
#define ARVORE_H
#include <QGraphicsView>
#include <QProcess>
#include <QTextStream>
#include <iostream>

using namespace std;
typedef struct Token {
  char info[21];
  int col;
  int linha;
  int tipo;
} Token;

typedef struct No {
  Token token;
  No *filho;
  No *prox;
  int num;
} No;

class Arvore {
public:
  void init(QGraphicsScene *scene, QGraphicsView *view);
  No *insereLista(No *l, Token tk);

  void show();
  No *getRaiz();
  void setRaiz(No *l);

protected:
private:
  QByteArray _prepareGraph();
  void _graphWalk(No *p, QTextStream *stream);

  No *_root;
  QGraphicsScene *_scene;
  QGraphicsView *_view;
};

#endif // ARVORE_H
