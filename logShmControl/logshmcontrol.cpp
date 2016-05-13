#include "logshmcontrol.h"


LogShmCreator::LogShmCreator(const char *path):LogShmControl()
{
    if (path == NULL)
        return;
    begin(path);
}

void LogShmCreator::writeLog(bool writeFunc(SystemLogInfo))
{
    vector<SysLogBlock *> vt;
    vt = getWriteableBlock();
    vector<SysLogBlock *>::iterator it;
    for(it = vt.begin(); it != vt.end(); it++){
        if ((*it)->blockStatus == SBS_FREE)
            continue; //skip free block!
        if ( !writeFunc((*it)->logInfo) ){
            cout << "WARNING:  wirtelog got warning by writeFunc faile!" << endl;
            continue; //WRITE LOG TO FILE FAILED!
        }
        if ((*it)->blockStatus == SBS_RETURNED){
            //returned block , means write the last log
            setBlockFree(*it);
        }
        else{
            //如果当前进程申请了多于初始时分配的block，则在写日志成功后重置其多出的block
            if (getCthBlockNumByPID( (*it)->ownerPID ) > INT_SHMLOG_SYS_BLOCK_INITIAL_COUNT)
                setBlockFree(*it);
            else
                (*it)->logStatus = LSS_AFTER_WRITE; //WIRTE FILE SUCCESS ,UPDATE BLOCK's logStatus;
        }
    }
}

int LogShmCreator::updateRqtBlockOwner(int pid, int blockNum)
{
    int rst = 0;
    if (!checkBlockInitialed())
        throw "ERROR: LogShmCreator::updateRqtBlockOwner fail cause by block not initialed!";
    for (int i = 0; i< getRqtCount() && blockNum > 0; i++){
        if (m_rqtBlocks[i].blockStatus == RLS_EMPTY){
            m_rqtBlocks[i].blockStatus = RLS_USR_GET;
            m_rqtBlocks[i].ownerPID = pid;
            blockNum--;
            rst++;
        }
    }
    return rst;
}

int LogShmCreator::updateSysBlockOwner(int pid, int blockNum)
{
    int rst = 0;
    if (!checkBlockInitialed())
        throw "ERROR: LogShmCreator::updateRqtBlockOwner fail cause by block not initialed!";
    for (int i = 0; i< getSysCount() && blockNum > 0; i++){
        if (m_sysBlocks[i].blockStatus == SBS_FREE){
            m_sysBlocks[i].blockStatus = SBS_CATCHED;
            m_sysBlocks[i].ownerPID = pid;
            blockNum--;
            rst++;
        }
    }
    return rst;
}


bool LogShmCreator::begin(const char *path)
{
    if (path == NULL)
        throw "ERROR,LogShmCtrl failed cause by NULL init-path when try to begin share memory!";
    strncpy(m_path,path,INT_WORKPATH_LENGTH);
    shmInitial();
    createInfos();
    getShmAddr();
    return blockInitials();
}

void LogShmCreator::end()
{

    //to dt shm , shm's imp and der must not null ,and block must not null ,but blocknum can be 0!
    if (m_rqtBlocks != NULL && checkShmInitialed()){
        if (m_rqtLogDer->DtShm(m_rqtBlocks) == -1)
            throw "ERROR,logShmCreator::end failed in rqt DtShm";
        if (m_rqtLogDer->ClearShm() == -1)
            throw "ERROR,logShmCreator::end failed in rqt ClearShm";
    }
    else
        throw "ERROR, logShmCreator end failed cause by m_rqtBlocks or m_rqtLogDer is null";

    if (m_sysBlocks != NULL && checkShmInitialed()){
        if (m_sysLogDer->DtShm(m_sysBlocks) == -1)
            throw "ERROR,logShmCreator::end failed in sys DtShm";
        if (m_sysLogDer->ClearShm() == -1)
            throw "ERROR,logShmCreator::end failed in sys ClearShm";
    }
    else
        throw "ERROR, logShmCreator end failed cause by m_sysBlocks or m_sysLogDer is null";
    return;
}


void LogShmCreator::shmInitial()
{

    //createor only do shmInitial once , all Imp and Der must be NULL!
    if (m_rqtLogDer != NULL || m_rqtLogImp != NULL || m_sysLogDer != NULL || m_sysLogImp != NULL )
        throw "ERROR, shmInitial failed case by logBlock not null!";


    ShmInitials tmp;
    //when initial, set block unit num to initial_macro
    setRqtCount(INT_SHMLOG_RQT_BLOCK_INITIAL_COUNT);
    setSysCount(INT_SHMLOG_SYS_BLOCK_INITIAL_COUNT);
    //create request shm link
    tmp.path = m_path;
    tmp.ipcKey = INT_SHMLOG_RQT_BLOCK_SHM_KEY;
    tmp.size = sizeof(stc_rqtLogBlock) * getRqtCount() + MIN_SHMLOG_SHAREMEMORY_SIZE;
    m_rqtLogImp = new ShareMemImp_Linux<stc_rqtLogBlock>(tmp);
    m_rqtLogDer = new IShareMemDerive<stc_rqtLogBlock>(*m_rqtLogImp);

    //create syslog shm link
    tmp.path = m_path;
    tmp.ipcKey = INT_SHMLOG_SYS_BLOCK_SHM_KEY;
    tmp.size = sizeof(stc_sysLogBlock) * getSysCount() + MIN_SHMLOG_SHAREMEMORY_SIZE;
    m_sysLogImp = new ShareMemImp_Linux<stc_sysLogBlock>(tmp);
    m_sysLogDer = new IShareMemDerive<stc_sysLogBlock>(*m_sysLogImp);

}


bool LogShmCreator::updateRqtValue(stc_rqtLogBlock value, int id)
{
    if (checkRqtId(id) == false)
        return false;
    for(int i = 0; i<getRqtCount(); i++)
    {
        if (m_rqtBlocks[i].blockID == id && m_rqtBlocks[i].blockStatus != RLS_USR_ASKED)
        {
            m_rqtBlocks[i] = value;
            return true;
        }
    }
    return false;
}

bool LogShmCreator::updateSysValue(stc_sysLogBlock value, int id)
{
    if (checkSysId(id) == false)
        return false;
    for(int i = 0; i<getSysCount(); i++)
    {
        if (m_sysBlocks[i].blockID == id && m_sysBlocks[i].blockStatus != SBS_FREE)
        {
            m_sysBlocks[i] = value;
            return true;
        }
    }
    return false;
}

void LogShmCreator::createInfos()
{
    if (checkShmInitialed()){
        if (m_rqtLogDer->CreateShmId() < 0)
            throw "ERROR:createInfos failed!";
        if (m_sysLogDer->CreateShmId() < 0)
            throw "ERROR:createInfos failed!";
    }
    else
        throw "ERROR: logShmCreator::CreateInfos failed by pointer is NULL!";
    return;
}

void LogShmCreator::getShmAddr()
{
    if (!checkShmInitialed())
        throw "ERROR: logShmCreator::GetShmAddr failed by pointer is NULL!";
    m_rqtBlocks = m_rqtLogDer->GetShmAddr();
    m_sysBlocks = m_sysLogDer->GetShmAddr();
    if (!checkBlockInitialed())
        throw "Error : can not get share memory address!";
    return;
}

void LogShmCreator::dtInfos()
{
    if ((!checkShmInitialed()) || m_rqtBlocks == NULL || m_sysBlocks == NULL)
        throw "ERROR: logShmCreator::DtInfos failed by pointer is NULL!";
    if (m_rqtLogDer->DtShm(m_rqtBlocks) < 0 || m_sysLogDer->DtShm(m_sysBlocks) < 0)
        throw "ERROR: logShmCreator::DtInfos failed by known reason!";
}

bool LogShmCreator::blockInitials()
{
    if (!checkBlockInitialed())
        return false;
    for (int i = 0; i < getRqtCount(); i++){
        m_rqtBlocks[i].blockID = i;
        m_rqtBlocks[i].rqtBlockTotal = getRqtCount();
        m_rqtBlocks[i].sysBlockTotal = getSysCount();
    }

    for (int j = 0; j < getSysCount(); j++){
        m_sysBlocks[j].blockID = j;
    }
    return true;
}

bool LogShmCreator::checkFreeRqtBlock()
{
    if (!checkRqtBlockInitialed())
        throw "ERROR:LogShmCreator::checkFreeRqtBlock fail cause by point not initialed!";
    int free = 0;
    for (int i = 0; i < getRqtCount(); i++){
        if (m_rqtBlocks[i].blockStatus == RLS_EMPTY)
            free++;
    }
    return ( float(free) > (FLOAT_SHMLOG_RQT_FREE_ARGU * float(getRqtCount()) )  );
}

bool LogShmCreator::checkFreeSysBlock()
{
    if (!checkSysBlockInitialed())
        throw "ERROR:LogShmCreator::checkFreeRqtBlock fail cause by point not initialed!";
    int free = 0;
    for (int i = 0; i < getSysCount(); i++){
        if (m_sysBlocks[i].blockStatus == SBS_FREE)
            free++;
    }
    return ( float(free) > (FLOAT_SHMLOG_SYS_FREE_ARGU * float(getSysCount()) )  );
}


vector<SysLogBlock *> LogShmCreator::getWriteableBlock()
{
    vector<SysLogBlock *> rst;
    if (getSysCount() <= 0 || m_sysBlocks == NULL)
        return rst;
    for (int i = 0; i<getSysCount(); i++){
        if (m_sysBlocks[i].logStatus == LSS_WAIT_WRITE_FILE && m_sysBlocks[i].blockStatus != SBS_FREE)
            rst.push_back(&(m_sysBlocks[i]));
    }
    return rst;
}



LogShmUser::LogShmUser():LogShmControl(),m_pid(-1)
{
    //DO NOTHING YET
}


bool LogShmUser::begin(const char *path, int pid)
{
    if (pid > 0)
        setPid(pid);
    if (path == NULL)
        throw "ERROR,LogShmUser failed cause by NULL init-path when try to begin share memory!";
    strncpy(m_path,path,INT_WORKPATH_LENGTH);
    //step 1, only connect one rqt stc_block , try to get total rqt block nums and sys block nums
    shmRqtInitial();
    getRqtShmAddr();

    //step 2, get whole shm cap ,use the nums which returned by step 1
    shmRqtInitial(m_rqtBlocks[0].rqtBlockTotal);
    shmSysInitial(m_rqtBlocks[0].sysBlockTotal);

    getRqtShmAddr();
    getSysShmAddr();
    //step 3, catch self blocks(set some block owner id to m_pid)
    catchBlocks(DEFAULT_SHMLOG_RQT_BLOCKNUM_EACHPID,DEFAULT_SHMLOG_SYS_BLOCKNUM_EACHPID);
    return true;
}

void LogShmUser::end()
{

    //to dt shm , shm's imp and der must not null ,and block must not null ,but blocknum can be 0!
    if (m_rqtBlocks != NULL && checkShmInitialed()){
        if (m_rqtLogDer->DtShm(m_rqtBlocks) == -1)
            throw "ERROR,logShmUser::end failed in rqt DtShm";
    }
    else
        throw "ERROR, logShmUser::end failed cause by m_rqtBlocks or m_rqtLogDer is null";

    if (m_sysBlocks != NULL && checkShmInitialed()){
        if (m_sysLogDer->DtShm(m_sysBlocks) == -1)
            throw "ERROR,logShmUser::end failed in sys DtShm";
    }
    else
        throw "ERROR, logShmUser::end failed cause by m_sysBlocks or m_sysLogDer is null";
    return;
}

void LogShmUser::insertNewLog(const SystemLogInfo &log)
{
    stc_sysLogBlock *temp = getBlock();

    if (temp == NULL){
        throw "ERROR,write log failed by no free shm!";
        return;
    }
    else{
        temp->logStatus = LSS_WAIT_WRITE_FILE;
        temp->logInfo = log;
    }
    return;
}

void LogShmUser::shmRqtInitial(int rqtSize)
{
    ShmInitials tmp;
    //when initial, set block unit num to initial_macro
    setRqtCount(rqtSize);

    //create request shm link
    tmp.path = m_path;
    tmp.ipcKey = INT_SHMLOG_RQT_BLOCK_SHM_KEY;
    tmp.size = sizeof(stc_rqtLogBlock) * getRqtCount() + MIN_SHMLOG_SHAREMEMORY_SIZE;
    m_rqtLogImp = new ShareMemImp_Linux<stc_rqtLogBlock>(tmp);
    m_rqtLogDer = new IShareMemDerive<stc_rqtLogBlock>(*m_rqtLogImp);
}

void LogShmUser::shmSysInitial(int sysSize)
{
    ShmInitials tmp;
    //when initial, set block unit num to initial_macro
    setSysCount(sysSize);

    //create request shm link
    tmp.path = m_path;
    tmp.ipcKey = INT_SHMLOG_SYS_BLOCK_SHM_KEY;
    tmp.size = sizeof(stc_sysLogBlock) * getSysCount() + MIN_SHMLOG_SHAREMEMORY_SIZE;
    m_sysLogImp = new ShareMemImp_Linux<stc_sysLogBlock>(tmp);
    m_sysLogDer = new IShareMemDerive<stc_sysLogBlock>(*m_sysLogImp);
}

int LogShmUser::connRqtInfo()
{
    if (checkRqtShmInitialed())
        return m_rqtLogDer->GetShmId();
    else
        return -1;
}

SysLogBlock *LogShmUser::getBlock()
{
    checkCthSysBlockState(); //check catched sys block status and recover it
    vector<int>::iterator it;
    int loopNum = INT_SHMLOG_FREE_BLOCK_LOOP_NUM_FOR_INSERT;
    stc_sysLogBlock *rst = NULL;
    while (rst == NULL && loopNum -- > 0) {
        for (it = m_cthSysIdx.begin(); it < m_cthSysIdx.end(); it++){
            if (m_sysBlocks[*it].blockStatus != SBS_CATCHED)
                throw "ERROR,found shm values chaos in getBlock()!";
            if (m_sysBlocks[*it].logStatus == LSS_AFTER_WRITE || m_sysBlocks[*it].logStatus == LSS_EMPTY)
                return &(m_sysBlocks[*it]);

        }
    }

    if (rst == NULL){ //no free loop now, ask new field;
        int i = cthNewBlock();
        if (i >= 0)
            rst = &(m_sysBlocks[i]);
    }
    return rst;
}

int LogShmUser::cthNewBlock()
{
    int rst = -1;
    //step 1 , try to got some free block
    for (int i = 0; i < getSysCount(); i++){
        if (m_sysBlocks[i].blockStatus == SBS_FREE){
            m_sysBlocks[i].blockStatus = SBS_CATCHED;
            m_sysBlocks[i].ownerPID = m_pid;
            m_sysBlocks[i].logStatus = LSS_EMPTY;
            m_cthSysIdx.push_back(i);
            return i;
        }
    }
    return rst;
}

void LogShmUser::checkCthSysBlockState()
{
    if (m_cthSysIdx.size() <= 0){
        cout << "Warning: no sys block be catched!" << endl;
        return;
    }

    vector<int>::iterator it;
    for (it = m_cthSysIdx.begin(); it != m_cthSysIdx.end(); it++ ){
        if (m_sysBlocks[*it].blockStatus != SBS_CATCHED || m_sysBlocks[*it].ownerPID != m_pid){
            m_cthSysIdx.erase(it);
            it--;
        }
    }
}

void LogShmUser::getRqtShmAddr()
{
    if (!checkRqtShmInitialed())
        throw "ERROR: logShmCreator::GetShmAddr failed by pointer is NULL!";
    m_rqtBlocks = m_rqtLogDer->GetShmAddr();
    if (!checkRqtBlockInitialed())
        throw "Error : can not get rqt share memory address!";
    return;
}

void LogShmUser::getSysShmAddr()
{
    if (!checkSysShmInitialed())
        throw "ERROR: logShmCreator::GetShmAddr failed by pointer is NULL!";
    m_sysBlocks = m_sysLogDer->GetShmAddr();
    if (!checkSysBlockInitialed())
        throw "Error : can not get rqt share memory address!";
    return;
}

void LogShmUser::catchBlocks(int rqtBlockNum, int sysBlockNum)
{
    if (!checkBlockInitialed())
        throw "ERROR: LogShmCreator::updateRqtBlockOwner fail cause by block not initialed!";
    for (int i = 0; i< getRqtCount() && rqtBlockNum > 0; i++){
        if (m_rqtBlocks[i].blockStatus == RLS_EMPTY){
            m_rqtBlocks[i].blockStatus = RLS_USR_GET;
            m_rqtBlocks[i].ownerPID = m_pid;
            m_cthRqtIdx.push_back(i);
            rqtBlockNum--;
        }
    }

    if (!checkBlockInitialed())
        throw "ERROR: LogShmCreator::updateRqtBlockOwner fail cause by block not initialed!";
    for (int j = 0; j< getSysCount() && sysBlockNum > 0; j++){
        if (m_sysBlocks[j].blockStatus == SBS_FREE){
            m_sysBlocks[j].blockStatus = SBS_CATCHED;
            m_sysBlocks[j].ownerPID = m_pid;
            m_cthSysIdx.push_back(j);
            sysBlockNum--;
        }
    }
}



bool LogShmUser::isOwnerRqtBlock(int bid)
{
    if (!checkBlockInitialed())
        return false;
    for (int i = 0; i < getRqtCount(); i++){
        if (m_rqtBlocks[i].blockID == bid && m_rqtBlocks[i].ownerPID == m_pid)
            return true;
    }
    return false;
}

bool LogShmUser::isOwnerSysBlock(int bid)
{
    if (!checkBlockInitialed())
        return false;
    for (int i = 0; i < getRqtCount(); i++){
        if (m_rqtBlocks[i].blockID == bid && m_rqtBlocks[i].ownerPID == m_pid)
            return true;
    }
    return false;
}




