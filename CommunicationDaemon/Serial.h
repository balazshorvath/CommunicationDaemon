#pragma once

class Serial{
	public:
		Serial(){
		}

		Serial(const char* device, int vmin, int vtime){
			_device = device;
			_vmin = vmin;
			_vtime = vtime;
			/*_device = (char*)malloc(strlen(device));
			memcpy(_device, device,strlen(device));
			*(_device + strlen(device)) = '\0';*/
		}

		~Serial(){
		}

		int OpenPort(){
			if(_device == "") return -1;
			struct termios opt;

			/* FLAGS: read/write | not become the process's controlling terminal
			| If possible, the file is opened in nonblocking mode O_NDELAY | */
			_descriptor = -1;
			_descriptor = open(_device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
			if(_descriptor == -1) {
				return -1;
			}
			tcgetattr(_descriptor, &opt);

			opt.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
			opt.c_iflag = IGNPAR;
			opt.c_oflag = 0;
			opt.c_lflag = 0;
			//opt.c_cc[VMIN] = _vmin;
			//opt.c_cc[VTIME] = _vtime;
			tcflush(_descriptor, TCIFLUSH);
			tcsetattr(_descriptor, TCSANOW, &opt);

			_isOpen = true;
			return 0;
		}
		void ClosePort(){
			close(_descriptor);
			_isOpen = false;
		}

		void SetDevice(const char* nDev){
			if(_isOpen) return;
			_device = nDev;
		}

		int SendBytes(char* data, char length){
			return write(_descriptor, data, length);
		}

		int RecvBytes(char* buffer, char length){
			return read(_descriptor, (void*)buffer, length);
		}

		int RecvNBytes(char* buffer, char buffLength, char nBytes){
			if(buffLength < nBytes) return -1;
			for(int i = 0; i< nBytes; i++) read(_descriptor, (void*)buffer++, 1);
			return 0;
		}

		int BytesToRead(){
			int bytes = 0;
			ioctl(_descriptor, FIONREAD, &bytes);
			return bytes;
		}
		void FlushIn(){
			tcflush(_descriptor, TCIFLUSH);
		}
		void FlushOut(){
			tcflush(_descriptor, TCOFLUSH);
		}
	private:
		std::string _device;
		int _descriptor;
		int _vmin, _vtime;
		bool _isOpen = false;
};
