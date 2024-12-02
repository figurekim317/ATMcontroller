import logging
from typing import Optional

def setup_logger(name: str, log_file: Optional[str] = None, level: int = logging.INFO) -> logging.Logger:
    """
    Sets up a logger with the given name.
    
    Args:
        name (str): Name of the logger.
        log_file (Optional[str]): Path to a log file. If provided, logs will also be written to this file.
        level (int): Logging level. Defaults to logging.INFO.
    
    Returns:
        logging.Logger: Configured logger.
    """
    logger = logging.getLogger(name)
    logger.setLevel(level)

    # Prevent duplicate handlers if the logger already exists
    if not logger.hasHandlers():
        # Console handler
        ch = logging.StreamHandler()
        ch.setFormatter(logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s'))
        logger.addHandler(ch)

        # File handler (optional)
        if log_file:
            fh = logging.FileHandler(log_file)
            fh.setFormatter(logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s'))
            logger.addHandler(fh)

    return logger

'''
이 코드는 로깅(logging) 기능을 설정하는 함수입니다. 로깅은 프로그램 실행 중에 발생하는 이벤트를 기록하고, 이를 디버깅, 문제 해결, 모니터링, 분석 등의 목적으로 사용하는 데 필요합니다.

왜 필요한가?
1. 디버깅과 문제 해결

로깅은 프로그램 실행 중의 정보를 기록하여 버그를 찾고 해결하는 데 도움을 줍니다.
예를 들어, 프로그램이 비정상적으로 종료되었을 때, 로그를 통해 어떤 함수에서 오류가 발생했는지 확인할 수 있습니다.
2. 실행 상태 모니터링

로깅을 사용하면 프로그램의 상태를 모니터링할 수 있습니다.
예: 프로그램이 특정 작업을 완료했는지, 특정 이벤트가 발생했는지 등을 로그로 기록.
3. 기록 및 감사

로그는 프로그램 사용 이력이나 중요한 이벤트(예: 사용자 로그인, 데이터베이스 업데이트 등)를 기록하는 데 유용합니다.
예: 보안 감사 및 컴플라이언스를 위한 로그 기록.
4. 프로덕션 환경에서의 문제 분석

실제 운영 환경에서는 디버깅 도구를 사용할 수 없으므로, 로깅을 통해 발생한 문제를 분석합니다.
'''