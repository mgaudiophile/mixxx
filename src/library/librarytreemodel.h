#ifndef LIBRARYTREEMODEL_H
#define LIBRARYTREEMODEL_H

#include <QHash>
#include <QPixmap>
#include <QSqlQuery>
#include <QStringList>

#include "library/treeitemmodel.h"

class CoverInfo;
class LibraryFeature;
class TrackCollection;

class LibraryTreeModel : public TreeItemModel {
    Q_OBJECT
  public:
    LibraryTreeModel(LibraryFeature* pFeature, 
                     TrackCollection* pTrackCollection, 
                     QObject* parent = nullptr);

    virtual QVariant data(const QModelIndex &index, int role) const;
    
    void setSortOrder(QStringList sortOrder);
    
  public slots:  
    void reloadTracksTree();
    
  private:
    
    struct CoverIndex {
        int iCoverHash;
        int iCoverLoc;
        int iTrackLoc;
        int iCoverSrc;
        int iCoverType;
    };
    
  private slots:
    void coverFound(const QObject* requestor, int requestReference, const CoverInfo&,
                    QPixmap pixmap, bool fromCache);
    
  private:    
    QString getQuery(TreeItem* pTree) const;
    void createTracksTree();
    void addCoverArt(const CoverIndex& index, const QSqlQuery& query, TreeItem* pTree);
    
    LibraryFeature* m_pFeature;
    TrackCollection* m_pTrackCollection;
    QStringList m_sortOrder;
    QStringList m_coverQuery;
    
    TreeItem* m_pLibraryItem;
    
};

#endif // LIBRARYTREEMODEL_H