from setuptools import find_packages
from setuptools import setup

setup(
    name='macspos_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('macspos_msgs', 'macspos_msgs.*')),
)
