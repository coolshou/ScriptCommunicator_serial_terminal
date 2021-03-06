#ifndef SINGLEDOCUMENT_H
#define SINGLEDOCUMENT_H

#include <QObject>
#include <Qsci/qsciscintilla.h>
#include <QDomDocument>
#include <QDateTime>



//A parsed ui object entry.
typedef struct
{
    QString objectName;
    QString uiFile;
}ParsedUiObject;

class MainWindow;


///This class holds a single document.
class SingleDocument : public QsciScintilla
{
public:
    SingleDocument(MainWindow* mainWindow, QWidget *parent = 0);

    ///Initializes the lexer.
    void initLexer(QString script);

    ///Updates the last modified time stamp.
    void updateLastModified(void);

    ///Returns the last modified time stamp.
    QDateTime getLastModified(void);

    ///Sets the document name/path.
    void setDocumentName(QString name, QFont font);

    ///Returns the document name/path.
    QString getDocumentName(void){return m_documentName;}

    ///Initializes the autocompletion.
    void initAutoCompletion(QStringList &additionalElements, QMap<QString, QStringList> &autoCompletionEntries, QMap<QString, QStringList>& autoCompletionApiFiles);

    ///Sets m_fileMustBeParsed.
    void setFileMustBeParsed(bool fileMustBeParsed){m_fileMustBeParsed = fileMustBeParsed;}

    ///Returns m_fileMustBeParsed.
    bool getFileMustBeParsed(void){return m_fileMustBeParsed;}

private:

    ///Checks if in the current document user interface files are loaded.
    ///If user interface are loaded then they will be parsed and added to the auto-completion
    ///list (g_autoCompletionEntries).
    void checkDocumentForUiFiles(QString currentText);

    ///Searches all dynamically created objects created by custom objects (like ScriptTimer).
    void checkDocumentForCustomDynamicObjects(QStringList &lines, QStringList& linesWithBrackets, QString& currentText, int passNumber);

    ///Searches all dynamically created objects created by standard objects (like String).
    void checkDocumentForStandardDynamicObjects(QStringList &lines, QStringList& linesWithBrackets, int passNumber);

    ///Parses an user interface file (auto-completion).
    void parseUiFile(QString uiFileName);

    ///Parse a widget list from a user interface file (auto-completion).
    void parseWidgetList(QDomElement& docElem, bool parseActions);

    ///Pointer to the main window.
    MainWindow* m_mainWindow;

    ///The name of the document.
    QString m_documentName;

    ///Time at which the corresponding file has been modified-
    QDateTime m_fileLastModified;

    ///True if the file must be parst (file content changed).
    bool m_fileMustBeParsed;
};

#endif // SINGLEDOCUMENT_H
