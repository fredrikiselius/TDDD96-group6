#ifndef BOOKMARKITEM_H
#define BOOKMARKITEM_H

#include "../Filehandler/bookmark.h"
#include <QListWidgetItem>

class BookmarkItem : public QListWidgetItem {
public:
    BookmarkItem(int frame_nbr, QString file_path, QString string, QListWidget* view);
    Bookmark* get_bookmark();
    int get_frame_number();
private:
    const int BOOKMARK_THUMBNAIL_HEIGHT = 64;
    Bookmark* bookmark;
};

#endif // BOOKMARKITEM_H
