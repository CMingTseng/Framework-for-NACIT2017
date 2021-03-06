#include "ncserver.h"

/*================================================================
 * 函数：CreateRecordFolders()
 *
 * 说明：
 *      创建记录文件夹；
 *      根目录在NCServer项目生成文件夹，在根目录下生成NCRecord文件夹，并在
 * NCRecord文件夹下生成以运行NCServer主程序起始时间为基础的文件夹，并在
 * 该文件夹中生成一系列记录文件；
 =================================================================
 */
void NCServer::CreateRecordFolders()
{
    if(RECORD)
    {
        // 创建Record根目录
        string rootName = "NCRecord/";
        CreateFolder(rootName);

        // 根据当前时间，创建该次记录的目录
        string timestr = "";
        timestr = getSysTime(TIME_NORMAL);
        rootName += "Record_";
        rootName += timestr;
        rootName += "/";
        CreateFolder(rootName);

        // 将当前文件夹名称赋值给NCServer类
        FolderPath = "./";
        FolderPath += rootName;
    }
}

/*================================================================
 * 函数：CreateRecordFiles()
 *
 * 说明：
 *      在文件夹中生成一系列记录文件；
 *      记录文件有：
 *      1. NCServer.dat文件，记录NCServer的收发
 *      2. NCImage.dat文件，记录NCImageClient的收发
 *      3. NCSend.dat文件，记录NCSendClient的收发
 *      4. NCInfo.dat文件，记录记录传感器数据随着时间的变化
 *      5. NCStage.dat文件，记录随着时间变化，NCStage以及对应Mission的变化状况
 *      6. NCElog.dat文件，记录连接状态以及错误报告；
 =================================================================
 */
void NCServer::CreateRecordFiles()
{
    if(RECORD)
    {
        string tmpName;

        // NCServer.dat文件，记录NCServer的收发
        tmpName = FolderPath;
        tmpName += "NCServer.dat";
        ServerStrm.open(tmpName.c_str(), ios::out | ios::app);
        if(!ServerStrm.is_open())
            cout<<"ERROR: NCServer.dat Open ERROR."<<endl;
        ServerStrm<<"#    NCServer.dat记录NCServer程序的收发记录"<<endl;
        ServerStrm<<"Time: "<<getSysTime(TIME_NORMAL)<<endl<<endl;

        // NCImage.dat文件，记录NCImageClient的收发
        tmpName = FolderPath;
        tmpName += "NCImage.dat";
        ImageStrm.open(tmpName.c_str(), ios::out | ios::app);
        if(!ImageStrm.is_open())
            cout<<"ERROR: NCImage.dat Open ERROR."<<endl;
        ImageStrm<<"#    NCImage.dat文件，记录NCImageClient的收发"<<endl;
        ImageStrm<<"Time: "<<getSysTime(TIME_STRING)<<endl<<endl;


        // NCSend.dat文件，记录NCSendClient的收发
        tmpName = FolderPath;
        tmpName += "NCSend.dat";
        SendStrm.open(tmpName.c_str(), ios::out | ios::app);
        if(!SendStrm.is_open())
            cout<<"ERROR: NCSend.dat Open ERROR."<<endl;
        SendStrm<<"#    NCSend.dat文件，记录NCSendClient的收发"<<endl;
        SendStrm<<"Time: "<<getSysTime(TIME_STRING)<<endl<<endl;

        // NCInfo.dat文件，记录记录传感器数据随着时间的变化
        tmpName = FolderPath;
        tmpName += "NCInfo.dat";
        InfoStrm.open(tmpName.c_str(), ios::out | ios::app);
        if(!InfoStrm.is_open())
            cout<<"ERROR: NCInfo.dat Open ERROR."<<endl;
        InfoStrm<<"#    NCInfo.dat文件，记录传感器数据随着时间的变化"<<endl;
        InfoStrm<<"Time: "<<getSysTime(TIME_STRING)<<endl<<endl;


        // NCStage.dat文件，记录随着时间变化，NCStage以及对应Mission的变化状况
        tmpName = FolderPath;
        tmpName += "NCStage.dat";
        StageStrm.open(tmpName.c_str(), ios::out | ios::app);
        if(!StageStrm.is_open())
            cout<<"ERROR: NCStage.dat Open ERROR."<<endl;
        StageStrm<<"#    NCStage.dat文件，记录随着时间变化，NCStage以及对应Mission的变化状况"<<endl;
        StageStrm<<"Time: "<<getSysTime(TIME_STRING)<<endl<<endl;

        // NCElog.dat文件，记录连接状态以及错误报告；
        tmpName = FolderPath;
        tmpName += "NCElog.dat";
        ElogStrm.open(tmpName.c_str(), ios::out | ios::app);
        if(!ElogStrm)
            cout<<"ERROR: NCElog.dat Open ERROR."<<endl;
        ElogStrm<<"#    NCElog.dat文件，记录连接状态以及错误报告"<<endl<<endl;
        ElogStrm<<"Time: "<<getSysTime(TIME_STRING)<<endl<<endl;

    }
}

/*================================================================
 * 函数：RecordNCServer(WORK_STATE state)
 *
 * 参数：
 *      WORK_STATE state: 需要记录的该条信息的收/发状态
 *          CS_RECV:    收
 *          CS_SEND:    发
 *
 * 说明：
 *      NCServer.dat文件，记录NCServer的收发
 =================================================================
 */
void NCServer::RecordNCServer(WORK_STATE state)
{
    if(RECORD)
    {
        if(ServerStrm)
        {
            switch(state)
            {
            case CS_RECV:
                ServerStrm<<"R"<<'\t';
                ServerStrm<<getSysTime(TIME_NOYMD_WITHMS)<<'\t';
                ServerStrm<<recv_msg<<endl;
                break;
            case CS_SEND:
                ServerStrm<<"S"<<'\t';
                ServerStrm<<getSysTime(TIME_NOYMD_WITHMS)<<'\t';
                ServerStrm<<input_msg<<endl;
                break;
            default:
                cout<<"ERROR: No This WORK_STATE in RecordNCServer()."<<endl;
                exit(0);
                break;
            }
        }
        else
            cout<<"ERROR: NCServer.dat Open ERROR."<<endl;
    }
}

/*================================================================
 * 函数：RecordNCImage(WORK_STATE state)
 *
 * 参数：
 *      WORK_STATE state: 需要记录的该条信息的收/发状态
 *          CS_RECV:    收
 *          CS_SEND:    发
 *
 * 说明：
 *      NCImage.dat文件，记录NCImageClient的收发
 *
 * 注：
 *      此处略去，师弟们请自行根据需要添加
 =================================================================
 */
void NCServer::RecordNCImage(WORK_STATE state)
{
    if(RECORD)
    {
        if(ImageStrm)
        {

        }
    }
}

/*================================================================
 * 函数：RecordNCSend(WORK_STATE state)
 *
 * 参数：
 *      WORK_STATE state: 需要记录的该条信息的收/发状态
 *          CS_RECV:    收
 *          CS_SEND:    发
 *
 * 说明：
 *      NCSend.dat文件，记录NCSendClient的收发
 *
 * 注：
 *      此处略去，师弟们请自行根据需要添加
 =================================================================
 */
void NCServer::RecordNCSend(WORK_STATE state)
{
    if(RECORD)
    {
        if(SendStrm)
        {

        }
    }
}

/*================================================================
 * 函数：RecordNCInfo()
 *
 * 说明：
 *      NCInfo.dat文件，记录记录传感器数据随着时间的变化
 *
 * 注：
 *      此处略去，师弟们请自行根据需要添加
 =================================================================
 */
void NCServer::RecordNCInfo()
{
    if(RECORD)
    {
        if(InfoStrm)
        {

        }
    }
}

/*================================================================
 * 函数：RecordNCInfo()
 *
 * 说明：
 *      NCStage.dat文件，记录随着时间变化，NCStage以及对应Mission的变化状况
 =================================================================
 */
void NCServer::RecordNCStage()
{
    if(RECORD)
    {
        if(StageStrm)
        {
            StageStrm<<getSysTime(TIME_NOYMD_WITHMS)<<'\t';
            // 输出当前CurStage的变量名称
            StageStrm<<typeid(*CurStage).name()<<'\t';
            // 输出当前CUrStage所处的Mission名称
            StageStrm<<getMission()<<endl;
        }
    }
}

/*================================================================
 * 函数：RecordNCElog(string EStr)
 *
 * 参数：
 *      string EStr:  需要记录的错误字符串
 *
 * 说明：
 *      NCElog.dat文件，记录连接状态以及错误报告；
 =================================================================
 */
void NCServer::RecordNCElog(string EStr)
{
    if(RECORD)
    {
        if(ElogStrm)
        {
            ElogStrm<<getSysTime(TIME_NOYMD_WITHMS)<<'\t';
            ElogStrm<<EStr<<endl;
        }
    }
}
