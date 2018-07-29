
#ifndef UTILITY_IMAGECOLORCHANGE_H
#define UTILITY_IMAGECOLORCHANGE_H

#include <vector>
#include <array>

#include <QColor>

#include <config/types.h>
#include <utility/interval.h>

class QImage;

namespace utility {

/*!
 * \brief Class that is used to swap colors in a QImage
 */
class ImageColorChange {

public:

    using ColorInterval = Interval<UIntegerType>;
    using ColorChList = std::vector<std::pair<QColor, std::array<ColorInterval, 3>> >;

    /*!
     * \brief Add a new swap interval to the ImageColorChange
     * \param r Interval for the red component
     * \param g Interval for the green component
     * \param b Interval for the blue component
     * \param new_color New color that will take the place when a pixel in the intervals is found
     * \sa changeImage(QImage&), colorChangeList(), clear()
     * \return true if it was added successfully, false otherwise
     */
    bool addChInterval(ColorInterval r, ColorInterval g, ColorInterval b, QColor new_color);

    /*!
     * \brief Change an image using the color intervals in the color change list
     * \param i The image that will be modified
     * \sa addChInterval(ColorInterval, ColorInterval, ColorInterval, QColor), colorChangeList()
     */
    void changeImage(QImage& i) const;

    /*!
     * \brief Clear all of the content of the color change list
     * \sa addChInterval(ColorInterval, ColorInterval, ColorInterval, QColor), colorChangeList()
     */
    void clear() { _clist.clear(); }

    /*!
     * \brief Return the list containing the colors change intervals
     * \sa addChInterval(ColorInterval, ColorInterval, ColorInterval, QColor), clear(), changeImage(QImage&)
     * \return A list with the colors intervals and new color values
     */
    const ColorChList& colorChangeList() const { return _clist; }

private:

    bool _verify_intervals(const ColorChList::value_type& v, const QColor& color) const {

        if(!v.second[0].inRange(color.red())) return false;
        if(!v.second[1].inRange(color.green())) return false;
        if(!v.second[2].inRange(color.blue())) return false;

        return true;
    }

    std::pair<QColor, bool> _get_new_color(const QColor& color) const {

        for(auto& v : _clist) if(_verify_intervals(v, color)) return { v.first, true };

        return { QColor(), false };
    }


    ColorChList _clist;
};

} /* namespace utility */

#endif // UTILITY_IMAGECOLORCHANGE_H
