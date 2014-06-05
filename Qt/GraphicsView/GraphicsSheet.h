/**
 * This work is licensed under the Creative Commons Attribution 3.0 Unported 
 * License. To view a copy of this license, visit 
 * http://creativecommons.org/licenses/by/3.0/ or send a letter to Creative 
 * Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 */

#include <QGraphicsView>
#include <QHash>

typedef  QGraphicsItem* (*FACTORY_FUNCTION)();

class GraphicsItemFactory {
    QHash<QString, FACTORY_FUNCTION> factoryFunctions;

public:
    GraphicsItemFactory();

    void registerItemClass(const QString& className, FACTORY_FUNCTION fac);

    QGraphicsItem* createItem(const QString& className);
};



class QGraphicsItem;
class QXmlStreamReader;
class QXmlStreamWriter;

class GraphicsScene : public QGraphicsScene {
public:
    GraphicsScene();

    QGraphicsItem* getItemAt(const QPointF & position);

    void readExternal(QXmlStreamReader& reader);

    void writeExternal(QXmlStreamWriter& writer);

    void saveToFile(const QString& fileName);

    void loadFromFile(const QString& fileName);

private:
    GraphicsItemFactory* itemFactory;
};


class ScaleWidget;
class ScaleEdgeWidget;
class Interactor;
class InteractableItem;
class Snapper;

class GraphicsSheet : public QGraphicsView {
    Q_OBJECT;

    QStringList sizeNames;
    QList<QSizeF> sizeDimensions;

    QStringList scaleNames;
    QList<float> scaleLevels;

    QStringList zoomNames;
    QList<float> zoomLevels;

    ScaleWidget* xScale;
    ScaleWidget* yScale;
    ScaleEdgeWidget* edge;

    float xScaleDPI;
    float yScaleDPI;

    float drawScale;    // e.g. 1:2 => 0.5
    float zoomScale;    // e.g. 50% => 0.5
    QSizeF sceneSize;   // e.g. 148x210
    bool landscape;     // true or false (landscape or portrait)

    Interactor* interactor;
    Snapper* snapper;

    void updateSize();

    QHash<QString, QPointF> points;

public:
    GraphicsSheet(QWidget* parent);

    void addSize(const QString& name, const QSizeF& size);

    void addPoint(const QString& name, const QPointF& point);
    void drawCoordinateSystem(QPainter* painter, const QTransform& t = QTransform(), const QColor& c = Qt::black);
    void drawPoints(QPainter* painter, const QHash<QString, QPointF>& points);

    QStringList getSizeNames() const;

    void addZoom(const QString& name, float level);

    QStringList getZoomNames() const;

    void addScale(const QString& name, float scale);

    QStringList getScaleNames() const;

    void setUnit(const QString& unit);

    void setScale(float scale);

    qreal getScale();

    void setZoom(float zoom);

    void setSize(const QSizeF& dimension);

    void setScaleBackground(const QColor& color);

    void setInteractor(Interactor* interactor);

    Interactor* getInteractor();

    InteractableItem* getFocusItem() const;

    void setSnapper(Snapper* snapper);

    virtual QPointF snap(const QPointF& pos);

    void setPositionIndicators(const QPointF& pos);

    /**
     * @return The size of a handle for an interactable item.
     */
    QSizeF getHandleSize();

public slots:
    void setScale(int idx);

    void setZoom(int idx);

    void setSize(int idx);

    void setDirection(int idx);

private slots:
    void areaMoved();

protected:
    // @Override
    virtual void drawBackground(QPainter * painter, const QRectF & rect);

    // @Override
    virtual void drawForeground ( QPainter * painter, const QRectF & rect );

    void resizeEvent ( QResizeEvent * event );

    QSize sizeHint() const;

    void mousePressEvent ( QMouseEvent * event );

    void mouseMoveEvent ( QMouseEvent * event );

    void mouseReleaseEvent ( QMouseEvent * event );

    void wheelEvent(QWheelEvent * event );

    void paste();
};
