
#include <QImage>

#include "imagecolorchange.h"

using namespace utility;

void ImageColorChange::changeImage(QImage& i) const {

    for(int y = 0; y < i.height(); y++){

        for(int x= 0; x < i.width(); x++){

            auto old_color = i.pixelColor(x, y);
            auto p = _get_new_color(old_color);

            if(!p.second) continue;

            QColor new_color = p.first;

            new_color.setAlpha(old_color.alpha());
            i.setPixelColor(x, y, new_color);
        }
    }
}

bool ImageColorChange::addChInterval(ColorInterval r, ColorInterval g, ColorInterval b, QColor new_color) {

    if(!r.isValid() || !g.isValid() || !b.isValid()) return false;

    _clist.emplace_back(new_color, ColorChList::value_type::second_type{ r, g, b });

    return true;
}
