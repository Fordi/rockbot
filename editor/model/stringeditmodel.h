#ifndef STRINGEDITMODEL_H
#define STRINGEDITMODEL_H

#include <QAbstractTableModel>
#include <string>
#include <vector>

#include "file/v4/file_strings.h"

class StringEditModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    StringEditModel(QObject *parent);
public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void set_data(std::vector<std::string> data);
    void set_pick_mode(bool pick_mode);

signals:

private:
    QObject *_parent;
    std::vector<std::string> string_list;
    bool pick_mode_enabled;

};

#endif // STRINGEDITMODEL_H
