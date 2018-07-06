#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

/*!
 * \brief Class used to display graphics itens in a scene
 * \sa BattleWidget
 */
class GraphicsView : public QGraphicsView {

public:

    class Handler;

    /*!
     * \brief Contructor for GraphicsView.
     * \param handler object that will handle events from this object.
     * \param parent this object parent, this parameter will be passed to QGraphicsView.
     */
    GraphicsView(Handler *handler, QWidget * parent = 0) : QGraphicsView(parent), _handler(handler) {}

    /*!
     * \brief Contructor for GraphicsView.
     * \param handler object that will handle events from this object.
     * \param scene scene that will be displayed by this object, this parameter will be passed to QGraphicsView.
     * \param parent this object parent, this parameter will be passed to QGraphicsView.
     */
    GraphicsView(Handler *handler, QGraphicsScene *scene, QWidget * parent = 0) : QGraphicsView(scene, parent), _handler(handler) {}

protected:

    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:

    Handler *_handler;
};

/*!
 * \brief A class inheriting from GraphicsView::Handler will be able to handle some events from GraphicsView.
 * \sa GraphicsView
 */
class GraphicsView::Handler {

public:

    /*!
     * \brief This method is called when a mouse move event ocurred inside the GraphicsView this object is handling
     */
    virtual void graphicsViewMouseMoveEvent(QMouseEvent *) {}

    /*!
     * \brief This method is called when a mouse press event ocurred inside the GraphicsView this object is handling
     */
    virtual void graphicsViewMousePressEvent(QMouseEvent *) {}

    /*!
     * \brief This method is called when a mouse release event ocurred inside the GraphicsView this object is handling
     */
    virtual void graphicsViewMouseReleaseEvent(QMouseEvent *) {}
};

#endif // GRAPHICSVIEW_H
