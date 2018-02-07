#ifndef Animation_H
#define Animation_H

#include <vector>
#include <bitset>
#include <random>

#include <QGraphicsItem>

#include "types.h"

/*!
 * \brief Abstraction for an animation.
 * \sa AnimatedObject
 */
class Animation {

    static const UIntegerType flags_quantity = 2;

public:

    enum class Flag : UIntegerType { RandomStart, Periodic };

    /*!
     * \brief Create an animation that represents sequancial images.
     * \sa AnimatedObject::next(), steps(), isPeriodic()
     * \param steps the number duration of the animation.
     * \param restart determine if the animation is cyclic or not.
     */
    explicit Animation(UIntegerType steps = 1, bool restart = false);

    Animation(const Animation& other) = default;
    Animation& operator=(const Animation& other) = default;

    /*!
     * \brief Add an QPixmap image to be displayed after some steps.
     * \sa AnimatedObject::next()
     * \param p pixmap image that will be displayed
     * \param initial_step time when the image will start beeing displayed
     */
    void addImage(const QPixmap& p, UIntegerType initial_step);

    /*!
     * \brief Set if the animation is cyclic or not.
     * \sa isPeriodic()
     * \param restart true if it's cyclic, false otherwise.
     */
    void setIsPeriodic(bool restart) { setFlag(Flag::Periodic, restart); }

    /*!
     * \brief Return if the animation is periodic.
     * \sa cyclic(), setIsPeriodic(bool)
     * \return true if it's periodic, false otherwise.
     */
    bool isPeriodic() const { return getFlag(Flag::Periodic); }

    /*!
     * \brief Same as 'isPeriodic'.
     * \sa isPeriodic()
     * \return true if it's cyclic, false otherwise.
     */
    bool cyclic() const { return isPeriodic(); }

    /*!
     * \brief Set if a flag is true or false.
     * \sa clearFlag(Flag), getFlag(Flag)
     * \param f flag that will be set.
     * \param value new value of the flag, by default true.
     */
    void setFlag(Flag f, bool value = true) { _flags[UIntegerType(f)] = value; }

    /*!
     * \brief Clear a flag, after this method is use it will be false, same as 'setFlag(f, false)'.
     * \sa setFlag(Flag, bool), getFlag(Flag)
     * \param f flag that will be cleaned.
     */
    void clearFlag(Flag f) { setFlag(f, false); }

    /*!
     * \brief Return the state of a flag.
     * \sa setFlag(Flag, bool), clearFlag(Flag)
     * \param f flag that will be returned.
     * \return true if it's set, false otherwise.
     */
    bool getFlag(Flag f) const { return _flags[UIntegerType(f)]; }

    /*!
     * \brief Change the duration of the animation.
     * \sa AnimatedObject::next(), steps()
     * \param steps New duration value.
     */
    void setSteps(UIntegerType steps);

    /*!
     * \brief Return the number of steps the animation have.
     * \sa AnimatedObject::next(), setSteps()
     * \return Number of steps the naimation have.
     */
    UIntegerType steps() const { return _steps; }

    /*!
     * \brief Return the image pixmap of an animation image.
     * \sa startingStep(UIntegerType), addImage(QPixmap, UIntegerType)
     * \param n number of the image sorted by startingStep value.
     * \return Pixmap image from the pixmap's added.
     */
    QPixmap pixmap(UIntegerType n) const { return _vector[n].first; }

    /*!
     * \brief Return the stating step an specific image is going to be displayed.
     * \sa pixmap(UIntegerType)
     * \param n number of the image sorted by startingStep value.
     * \return starting step of a image in the animation.
     */
    UIntegerType startingStep(UIntegerType n) const { return _vector[n].second; }

    /*!
     * \brief Return the number of images.
     * \sa addImage(QPixmap, UIntegerType)
     * \return number of images in the animation.
     */
    UIntegerType images() const { return _vector.size(); }

private:

    std::vector<std::pair<QPixmap, UIntegerType> > _vector;

    UIntegerType _steps;

    std::bitset<flags_quantity> _flags;
};

#endif // Animation_H
