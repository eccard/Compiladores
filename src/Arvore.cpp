#include "Arvore.h"
//#include <iostream>

void Arvore::init(QGraphicsScene *scene, QGraphicsView *view) {
  this->_root = NULL;
  this->_scene = scene;
  this->_view = view;
}
No *Arvore::getRaiz() { return this->_root; }
void Arvore::setRaiz(No *l) { this->_root = l; }

No *Arvore::insereLista(No *l, Token tk) {
  No *r = l;
  No *t = NULL;
  if (l == NULL) {
    l = (No *)malloc(sizeof(No));
    l->token = tk;
    l->prox = NULL;
    l->filho = NULL;

    return l;
  } else {

    while (r->prox != NULL) {
      r = r->prox;
    }

    t = (No *)malloc(sizeof(No));
    t->token = tk;
    t->prox = NULL;
    t->filho = NULL;
    r->prox = t;
    return l;
  }
}

void Arvore::_graphWalk(No *p, QTextStream *stream) {
  if (p != NULL) {
    if (p->prox != NULL) {

      //            std::cout<< "\t\ta"<< p->num <<"[label=\""<< p->token.info
      //            << "\"];"<<std::endl; std::cout << "\t\ta"<< p->prox->num
      //            <<"[label=\""<< p->prox->token.info << "\"];"<<std::endl;
      //            std::cout<< "\t\ta"<<p->num<<" -> a"<< p->prox->num<<
      //            std::endl; std::cout<< "\t\t" << "{rank=same a"<<p->num<< "
      //            a"<<p->prox->num<<"};"<<std::endl;

      *stream << "\t\ta" << p->num << "[label=\"" << p->token.info << "\"];"
              << endl;
      *stream << "\t\ta" << p->prox->num << "[label=\"" << p->prox->token.info
              << "\"];" << endl;
      *stream << "\t\ta" << p->num << " -> a" << p->prox->num << endl;
      *stream << "\t\t"
              << "{rank=same a" << p->num << " a" << p->prox->num << "};"
              << endl;
      this->_graphWalk(p->prox, stream);
    }

    if (p->filho != NULL) {

      //            std::cout<< "\t\ta"<< p->num<<"[label=\""<< p->token.info <<
      //            "\"];"<<std::endl; std::cout<< "\t\ta"<< p->filho->num
      //            <<"[label=\""<< p->filho->token.info << "\"];"<<std::endl;
      //            std::cout<< "\t\ta"<< p->num <<" -> a"<< p->filho->num <<
      //            std::endl;

      *stream << "\t\ta" << p->num << "[label=\"" << p->token.info << "\"];"
              << endl;
      *stream << "\t\ta" << p->filho->num << "[label=\"" << p->filho->token.info
              << "\"];" << endl;
      *stream << "\t\ta" << p->num << " -> a" << p->filho->num << endl;
      this->_graphWalk(p->filho, stream);
    }
  }
}
QByteArray Arvore::_prepareGraph() {
  QByteArray a = QByteArray();

  QTextStream stream(&a, QIODevice::ReadWrite);
  stream << "digraph G{" << endl;
  stream << "\tnode[fontsize=10,margin=0,width=\".4\", height=\".3\"];" << endl;
  this->_graphWalk(this->_root, &stream);
  stream << "\t}" << endl;
  stream.flush();

  return a;
}

void Arvore::show() {
  QProcess *p = new QProcess();
  QByteArray a = this->_prepareGraph();

  p->setProcessChannelMode(QProcess::MergedChannels);
  p->start("dot", QStringList() << "-Tpng");
  p->write(a);
  p->closeWriteChannel();

  QByteArray data;
  QPixmap pixmap = QPixmap();

  while (!p->waitForFinished()) {}

  data = p->readAll();

  pixmap.loadFromData(data);

  this->_scene->addPixmap(pixmap);
  this->_view->show();

  delete p;
}

/*

  node[fontsize=10,margin=0,width=.4, height=.3];

  dot -Tpng >t1.png
    digraph G{
    main->parse->test;
    test->dois;
    {rank=same test dois}
    dois->tres;
    tres->quatro;
    {rank=same tres quatro}
    quatro->cinco;
    {rank=same quatro cinco}
}

digraph G {
  rankdir=LR
  node1->node2->node3->node4
  node1_1->node4_1;
  {rank=same node1 node1_1}
  {rank=same node4 node4_1}
}


*/
