#ifndef BOOKMARKITEM_H
#define BOOKMARKITEM_H

#include "bookmark.h"
#include <QListWidgetItem>

class BookmarkItem : public QListWidgetItem {
public:
    BookmarkItem(int frame_nbr, std::string file_path, QString string, QListWidget* view);
    BookmarkItem(Bookmark bookmrk, QListWidget* view);
    Bookmark* get_bookmark();
    int get_frame_number();
private:
    void create_thumbnail(std::string file_path);
    const int BOOKMARK_THUMBNAIL_HEIGHT = 64;
    Bookmark* bookmark;
};

#endif // BOOKMARKITEM_H
