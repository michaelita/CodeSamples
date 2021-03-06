#ifndef INTERACTABLEITEM_H
#define INTERACTABLEITEM_H

#include <QObject>


class QPointF;
class GraphicsSheet;
class QXmlStreamWriter;
class QXmlStreamReader;
class QPainter;

typedef unsigned int AbstractEditHandle;


#ifdef EXP_SYMBOLS
class Q_DECL_EXPORT InteractableItem : public QObject {
#else
class Q_DECL_IMPORT InteractableItem : public QObject {
#endif

    Q_OBJECT;

public:

    virtual ~InteractableItem() {};

    virtual AbstractEditHandle getEditHandle(GraphicsSheet* view, const QPointF& pos, AbstractEditHandle enabledHandles = 0xffff) = 0;

    virtual void paintHandles(GraphicsSheet* view, QPainter * painter, AbstractEditHandle enabledHandles = 0xffff) = 0;

    virtual QPointF getHandleOffset(AbstractEditHandle editHandle, const QPointF& scenePos) = 0;

    virtual void moveHandle(AbstractEditHandle editHandle, const QPointF& scenePos) = 0;

    virtual void setCursor(GraphicsSheet* theView, AbstractEditHandle handle) = 0;

    virtual void paintSelectedBorder(GraphicsSheet* view, QPainter * painter) = 0;

    virtual void setItemSelected(bool sel) = 0;

    virtual QPointF getNearestEdge(GraphicsSheet* theView, const QPointF& scenePos) = 0;

// Interface: Serializable
    virtual void writeExternal(QXmlStreamWriter& writer) = 0;
    virtual void readExternal(QXmlStreamReader& reader) = 0;

signals:
    void propertyChanged();

};

#endif
