#!/bin/sh

rm -rf ~/.local/share/tl_ub
mkdir ~/.local/share/tl_ub
cp work_init_c_run ~/.local/share/tl_ub/tl_ub_c
cp work_init_client.sh ~/.local/share/tl_ub/tl_ub_c.sh
sudo ln -s $HOME/.local/share/tl_ub/tl_ub_c /usr/local/bin/ubtw
sudo ln -s $HOME/.local/share/tl_ub/tl_ub_c.sh /usr/local/bin/ubtw1

ZSHR=$( cat $HOME/.zshrc )

if [ -n "$ZSHR" ]; then
	ZSH_EX=$( /bin/zsh --login -c 'source ~/.zshrc && echo $HOST_TL' )
	if [ -z "$ZSH_EX" ]; then
		echo "export HOST_TL=localhost" >> ~/.zshrc 
		echo "export PORT_TL=9443" >> ~/.zshrc
	fi
	source ~/.zshrc
else
	BASH_EX=$( /bin/bash --login -c 'echo $HOST_TL' )
	if [ -z "$BASH_EX" ]; then
		echo "export HOST_TL=localhost" >> ~/.bashrc 
		echo "export PORT_TL=9443" >> ~/.bashrc
	fi
	source ~/.bashrc
fi

