/* Serial Port Class for Windows
 *
 * https://github.com/HiOtto/SerialPortWindows
 *
 * Copyright (c) 2014 Siqi Liu
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */



#ifndef SERIALPORT_H_
#define SERIALPORT_H_

#include <Windows.h>
#include <fstream>


class CSerialPort
{
public:
	CSerialPort(void);
	~CSerialPort(void);

public:
	
	/** InitPort
	 *
	 *  @param:  UINT portNo
	 *  @param:  UINT baud
	 *  @param:  char parity
	 *  @param:  UINT databitss
	 *  @param:  UINT stopsbits
	 *  @param:  DWORD dwCommEvents  EV_RXCHAR, only one byte can update event
	 *  @return: bool  If the initialization is successful
	 *  @note:   
	 *  @see:    
	 */
	bool InitPort( UINT  portNo = 1,UINT  baud = CBR_9600,char  parity = 'N',UINT  databits = 8, 
		           UINT  stopsbits = 1,DWORD dwCommEvents = EV_RXCHAR);

	/** InitPort
	 *
	 *  Set COM with DCB
	 *  @param:  UINT portNo
	 *  @param:  const LPDCB & plDCB
	 *  @return: bool  If the initialization is successful
	 *  @note:   With DCB constructed by yourself
	 *  @see:    
	 */
	bool InitPort( UINT  portNo ,const LPDCB& plDCB );

	/** OpenListenThread
	 *
	 *  Listen the COM data and printf
	 *  @return: bool  If open thread successfully
	 *  @note:   If thread is opened, return flase
	 *  @see:    
	 */
	bool OpenListenThread();

	/** CloseListenTread
	 *
	 *  
	 *  @return: bool  If close thread successfully
	 *  @note:   If thread is closed, return flase
	 *  @see:    
	 */
	bool CloseListenTread();

    /** WriteData
	 *
	 *  
	 *  @param:  unsigned char * pData
	 *  @param:  unsigned int length
	 *  @return: bool
	 *  @note:   The data should not exceed the length limitation
	 *  @see:    
	 */
	bool WriteData(unsigned char* pData, unsigned int length);

	/** GetBytesInCOM
	 *
	 *  Get Bytes length in COM
	 *  @return: UINT  
	 *  @note:   If there is no data, return 0
	 *  @see:    
	 */
	UINT GetBytesInCOM();

	/** Get one byte from COM
	 *
	 *  
	 *  @param:  char & cRecved
	 *  @return: bool
	 *  @note:   
	 *  @see:    
	 */
	bool ReadChar(char &cRecved);

private:

	/** �򿪴���
	 *
	 *  
	 *  @param:  UINT portNo �����豸��
	 *  @return: bool  ���Ƿ�ɹ�
	 *  @note:   
	 *  @see:    
	 */
	bool openPort( UINT  portNo );

	/** �رմ���
	 *
	 *  
	 *  @return: void  �����Ƿ�ɹ�
	 *  @note:   
	 *  @see:    
	 */
	void ClosePort();
	
	/** ���ڼ����߳�
	 *
	 *  �������Դ��ڵ����ݺ���Ϣ
	 *  @param:  void * pParam �̲߳���
	 *  @return: UINT WINAPI �̷߳���ֵ
	 *  @note:   
	 *  @see:    
	 */
	static UINT WINAPI ListenThread(void* pParam);

private:

	/** ���ھ�� */ 
	HANDLE  m_hComm;

	/** �߳��˳���־���� */ 
	static bool s_bExit;

	/** �߳̾�� */ 
	volatile HANDLE    m_hListenThread;

	/** ͬ������,�ٽ������� */ 
	CRITICAL_SECTION   m_csCommunicationSync;       //!< �����������


};

#endif //SERIALPORT_H_