
#ifndef UTILITY_IMAGECOLORCHANGE_H
#define UTILITY_IMAGECOLORCHANGE_H

#include <vector>
#include <array>

#include <QColor>
#include <QImage>

#include <config/types.h>
#include <utility/interval.h>

namespace utility {

class ImageColorChange {

public:

    using ColorInterval = Interval<UIntegerType>;
    using ColorChList = std::vector<std::pair<QColor, std::array<ColorInterval, 3>> >;

    void changeImage(QImage& i) const {

        for(int y = 0; y < i.height(); y++){

            for(int x= 0; x < i.width(); x++){

                auto old_color = i.pixelColor(x, y);
                auto p = _get_new_color(old_color);

                if(!p.second) continue;

                QColor new_color = p.first;

                new_color.setAlpha(old_color.alpha());
                i.setPixelColor(x,y,new_color);
            }
        }
    }

    bool addChInterval(ColorInterval r, ColorInterval g, ColorInterval b, QColor new_color) {

        if(!r.isValid() || !g.isValid() || !b.isValid()) return false;

        _clist.emplace_back(new_color, ColorChList::value_type::second_type{ r, g, b });

        return true;
    }

    void clear() { _clist.clear(); }

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
