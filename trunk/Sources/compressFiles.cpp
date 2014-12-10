/* 2007-11-07                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2008-09-27

/*! @brief Komprimieren von Dateien mit zip. zip
*   muss sich im gleichen Verzeichnis befinden wie das Programm "PanConverter".
*/

void MainWindow::compressFile( const QString &s_FilenameIn )
{
    QFileInfo fi( s_FilenameIn );

    QProcess process;

// **********************************************************************************************

    #if defined(Q_OS_LINUX)
        process.start( "zip -j \"" + QDir::toNativeSeparators( fi.absolutePath() + "/" + fi.completeBaseName() + ".zip" ) + "\"" + " \"" + QDir::toNativeSeparators( s_FilenameIn ) + "\"" );
        process.waitForFinished();
    #endif

    #if defined(Q_OS_MAC)
        process.start( "zip -j \"" + QDir::toNativeSeparators( fi.absolutePath() + "/" + fi.completeBaseName() + ".zip" ) + "\"" + " \"" + QDir::toNativeSeparators( s_FilenameIn ) + "\"" );
        process.waitForFinished();
    #endif

    #if defined(Q_OS_WIN)
        process.start( "7z a \"" + QDir::toNativeSeparators( fi.absolutePath() + "/" + fi.completeBaseName() + ".zip" ) + "\"" + " \"" + QDir::toNativeSeparators( s_FilenameIn ) + "\"" );
        process.waitForFinished();
    #endif

// **********************************************************************************************

    return;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doCompressFiles()
{
    int		i                   = 0;
    int		err                 = 0;
    int		stopProgress        = 0;

// **********************************************************************************************

    if ( existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList ) == true )
    {
        initFileProgress( gsl_FilenameList.count(), gsl_FilenameList.at( 0 ), tr( "Compressing files ..." ) );

        while ( ( i < gsl_FilenameList.count() ) && ( err == _NOERROR_ ) && ( stopProgress != _APPBREAK_ ) )
        {
            setStatusBar( tr( "Compress " ) + QDir::toNativeSeparators( gsl_FilenameList.at( i ) ) + tr( " ..." ) );

            compressFile( gsl_FilenameList.at( i ) );

            stopProgress = incFileProgress( gsl_FilenameList.count(), ++i );
        }

        resetFileProgress( gsl_FilenameList.count() );
    }
    else
    {
        err = _CHOOSEABORTED_;
    }

// **********************************************************************************************

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Compress files was canceled" ), true );

    onError( err );
}
